"""
Constant tables (LUT) written in the headers by the implementation templates, computed here at generation time
instead of being written by hand in the JSON files.

The templates call these functions as Jinja globals (see `TEMPLATE_GLOBALS` and
`codegen/candidate_resolver.render_template`), and get a C initializer:

    static const uint8_t lut[16][16] = {{ compress_lut(lanes=4, units=4, fill=128) }};

The initializer is written `{ {a, b}, {c, d} }`: a `{{` in the JSON would start a Jinja expression.
"""


def _initializer(rows):
    """C initializer of a 2D array: `{ {a, b}, {c, d} }`."""
    return "{ " + ", ".join("{" + ", ".join(str(v) for v in row) + "}" for row in rows) + " }"


def compress_lut(lanes, units, fill=None):
    """
    Table of `compress` by permutation: one row per value of the mask (bit k set: lane k active, 2^lanes rows), giving
    the source of each unit of the result. A lane is made of `units` consecutive units (bytes for `pshufb` / `tbl`,
    32-bit lanes for `vpermps`): the active lanes are packed first, in order, then the units after the count are
    `fill`, or the units of the lane 0 when `fill` is None (their value is then masked by the caller).

        compress_lut(4, 4, 128)  # SSSE3, 32-bit lanes: bytes for pshufb, 128 gives a zero byte
        compress_lut(4, 4, 255)  # NEON: tbl gives a zero byte for an index out of the table
        compress_lut(8, 1)       # AVX2, 32-bit lanes: lane indices for vpermps, zeroed after the count by an and
        compress_lut(4, 2)       # AVX2, 64-bit lanes: pairs of 32-bit lane indices for vpermps
    """
    rows = []
    for mask in range(1 << lanes):
        active = [k for k in range(lanes) if mask >> k & 1]
        row = []
        for slot in range(lanes):
            for u in range(units):
                if slot < len(active):
                    row.append(active[slot] * units + u)
                else:
                    row.append(u if fill is None else fill)
        rows.append(row)
    return _initializer(rows)


# functions available in every implementation template
TEMPLATE_GLOBALS = {
    "compress_lut": compress_lut,
}
