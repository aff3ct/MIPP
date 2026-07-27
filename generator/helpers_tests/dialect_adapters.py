"""
Dialect Adapters for MIPP Test Generation.
Provides abstract base and concrete implementations for C, C++, and C++ Obj dialects.
"""

from abc import ABC, abstractmethod


class DialectAdapter(ABC):
    @property
    @abstractmethod
    def name(self) -> str:
        pass

    @abstractmethod
    def format_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_scalar_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_scalar_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_scalar_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_scalar_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"{self.format_get_func_name(dt_ext, lmul_suffix)}({reg_name}, {index_expr})"

    def format_scalar_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"{self.format_scalar_get_func_name(dt_ext, lmul_suffix)}({reg_name}, {index_expr})"

    def format_get_k(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"{self.format_get_k_func_name(dt_ext, lmul_suffix)}({reg_name}, {index_expr})"

    def format_scalar_get_k(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"{self.format_scalar_get_k_func_name(dt_ext, lmul_suffix)}({reg_name}, {index_expr})"

    def format_get_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    def format_scalar_get_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    def format_get_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    def format_scalar_get_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    @abstractmethod
    def format_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        pass

    @abstractmethod
    def format_scalar_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        pass

    @abstractmethod
    def format_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        pass

    @abstractmethod
    def format_scalar_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        pass


class CppDialectAdapter(DialectAdapter):
    @property
    def name(self) -> str:
        return "cpp"

    def format_type(self, dt_ext: str) -> str:
        if not dt_ext or dt_ext == "T":
            return "T"
        type_map = {
            "int32": "int32_t", "int64": "int64_t", "int16": "int16_t", "int8": "int8_t",
            "uint32": "uint32_t", "uint64": "uint64_t", "uint16": "uint16_t", "uint8": "uint8_t",
            "float32": "float", "float64": "double"
        }
        return type_map.get(dt_ext, dt_ext)

    def format_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "auto"

    def format_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "auto"

    def format_scalar_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "auto"

    def format_scalar_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "auto"

    def format_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        if lmul_suffix and lmul_suffix not in ("", "m1", "m0"):
            coeff = lmul_suffix[1:] if lmul_suffix.startswith("m") else (f"-{lmul_suffix[1:]}" if lmul_suffix.startswith("d") else "1")
            return f"mipp::load<T, {coeff}>({ptr_name})"
        return f"mipp::load<T>({ptr_name})"

    def format_scalar_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        if lmul_suffix and lmul_suffix not in ("", "m1", "m0"):
            coeff = lmul_suffix[1:] if lmul_suffix.startswith("m") else (f"-{lmul_suffix[1:]}" if lmul_suffix.startswith("d") else "1")
            return f"mipp::load<T, {coeff}, mipp::ISA::SCALAR>({ptr_name})"
        return f"mipp::load<T, 1, mipp::ISA::SCALAR>({ptr_name})"

    def format_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        t_str = self.format_type(dt_ext)
        if lmul_suffix and lmul_suffix not in ("", "m1", "m0"):
            coeff = lmul_suffix[1:] if lmul_suffix.startswith("m") else (f"-{lmul_suffix[1:]}" if lmul_suffix.startswith("d") else "1")
            return f"mipp::set_k<{t_str}, {coeff}>({ptr_name})"
        return f"mipp::set_k<{t_str}>({ptr_name})"

    def format_scalar_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        t_str = self.format_type(dt_ext)
        if lmul_suffix and lmul_suffix not in ("", "m1", "m0"):
            coeff = lmul_suffix[1:] if lmul_suffix.startswith("m") else (f"-{lmul_suffix[1:]}" if lmul_suffix.startswith("d") else "1")
            return f"mipp::set_k<{t_str}, {coeff}, mipp::ISA::SCALAR>({ptr_name})"
        return f"mipp::set_k<{t_str}, 1, mipp::ISA::SCALAR>({ptr_name})"

    def format_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"mipp::get({reg_name}, {index_expr})"

    def format_scalar_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"mipp::get({reg_name}, {index_expr})"

    def format_get_k(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"mipp::get({reg_name}, {index_expr})"

    def format_scalar_get_k(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"mipp::get({reg_name}, {index_expr})"

    def format_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        fname = func_name
        if fname in ("andb_k", "orb_k", "xorb_k", "notb_k", "andnb_k"):
            fname = fname[:-2]
        coeff = lmul_suffix[1:] if (lmul_suffix and lmul_suffix.startswith("m") and lmul_suffix != "m0") else (f"-{lmul_suffix[1:]}" if (lmul_suffix and lmul_suffix.startswith("d")) else "1")
        if mkind == "mask":
            return f"mipp::{fname}<mipp::M, T, {coeff}>({args_str})"
        elif mkind == "maskz":
            return f"mipp::{fname}<mipp::Z, T, {coeff}>({args_str})"
        elif mkind == "masks":
            return f"mipp::{fname}<mipp::S, T, {coeff}>({args_str})"
        if fname in ("cast", "cast_k", "cvt", "wcvt"):
            base_fname = "cast" if fname == "cast_k" else fname
            dt_dst = dt_ext.split(",")[-1].split("_")[-1]
            return f"mipp::{base_fname}_{dt_dst}({args_str})"
        if fname in ("set", "set_k", "set1", "set1_k", "set0", "set0_k", "load", "loadu"):
            if coeff != "1":
                return f"mipp::{fname}<T, {coeff}>({args_str})"
            return f"mipp::{fname}<T>({args_str})"
        return f"mipp::{fname}({args_str})"

    def format_scalar_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        fname = func_name
        if fname in ("andb_k", "orb_k", "xorb_k", "notb_k", "andnb_k"):
            fname = fname[:-2]
        coeff = lmul_suffix[1:] if (lmul_suffix and lmul_suffix.startswith("m") and lmul_suffix != "m0") else (f"-{lmul_suffix[1:]}" if (lmul_suffix and lmul_suffix.startswith("d")) else "1")
        if mkind == "mask":
            return f"mipp::{fname}<mipp::M, T, {coeff}, mipp::ISA::SCALAR>({args_str})"
        elif mkind == "maskz":
            return f"mipp::{fname}<mipp::Z, T, {coeff}, mipp::ISA::SCALAR>({args_str})"
        elif mkind == "masks":
            return f"mipp::{fname}<mipp::S, T, {coeff}, mipp::ISA::SCALAR>({args_str})"
        if fname in ("cast", "cast_k", "cvt", "wcvt"):
            base_fname = "cast" if fname == "cast_k" else fname
            dt_dst = dt_ext.split(",")[-1].split("_")[-1]
            return f"mipp::{base_fname}_{dt_dst}({args_str})"
        if fname in ("set", "set_k", "set1", "set1_k", "set0", "set0_k", "load", "loadu"):
            return f"mipp::{fname}<T, {coeff}, mipp::ISA::SCALAR>({args_str})"
        return f"mipp::{fname}({args_str})"

    def format_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        return f"mipp::tomsk({reg_name})"

    def format_scalar_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        return f"mipp::tomsk({reg_name})"


class CDialectAdapter(DialectAdapter):
    @property
    def name(self) -> str:
        return "c"

    def format_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"rvd_{dt_ext}{suffix}_t"

    def format_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"rvm_{dt_ext}{suffix}_t"

    def format_scalar_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"rvd_scalar_{dt_ext}{suffix}_t"

    def format_scalar_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"rvm_scalar_{dt_ext}{suffix}_t"

    def format_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_load_{dt_ext}{suffix}({ptr_name})"

    def format_scalar_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_load_{dt_ext}{suffix}({ptr_name})"

    def format_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_set_k_{dt_ext}{suffix}({ptr_name})"

    def format_scalar_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_set_k_{dt_ext}{suffix}({ptr_name})"

    def format_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_get_{dt_ext}{suffix}({reg_name}, {index_expr})"

    def format_scalar_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_get_{dt_ext}{suffix}({reg_name}, {index_expr})"

    def format_get_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_get_{dt_ext}{suffix}"

    def format_scalar_get_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_get_{dt_ext}{suffix}"

    def format_get_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_get_k_{dt_ext}{suffix}"

    def format_scalar_get_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_get_k_{dt_ext}{suffix}"

    def format_scalar_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_get_{dt_ext}{suffix}({reg_name}, {index_expr})"

    def format_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        if mkind in ("mask", "maskz", "masks"):
            return f"mipp_{func_name}_{dt_ext}_{mkind}{suffix}({args_str})"
        return f"mipp_{func_name}_{dt_ext}{suffix}({args_str})"

    def format_scalar_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        if mkind in ("mask", "maskz", "masks"):
            return f"mipp_scalar_{func_name}_{dt_ext}_{mkind}{suffix}({args_str})"
        return f"mipp_scalar_{func_name}_{dt_ext}{suffix}({args_str})"

    def format_load_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_load_{dt_ext}{suffix}"

    def format_scalar_load_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_load_{dt_ext}{suffix}"

    def format_set_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_set_k_{dt_ext}{suffix}"

    def format_scalar_set_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_set_k_{dt_ext}{suffix}"

    def format_func_name(self, func_name: str, dt_ext: str, lmul_suffix: str = "", mkind: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        if mkind in ("mask", "maskz", "masks"):
            return f"mipp_{func_name}_{dt_ext}_{mkind}{suffix}"
        return f"mipp_{func_name}_{dt_ext}{suffix}"

    def format_scalar_func_name(self, func_name: str, dt_ext: str, lmul_suffix: str = "", mkind: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        if mkind in ("mask", "maskz", "masks"):
            return f"mipp_scalar_{func_name}_{dt_ext}_{mkind}{suffix}"
        return f"mipp_scalar_{func_name}_{dt_ext}{suffix}"

    def format_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_tomsk_{dt_ext}{suffix}({reg_name})"

    def format_scalar_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        suffix = f"_{lmul_suffix}" if lmul_suffix and lmul_suffix not in ("", "m0") else ""
        return f"mipp_scalar_tomsk_{dt_ext}{suffix}({reg_name})"


class CppObjDialectAdapter(DialectAdapter):
    op_syms = {
        "add": "+", "sub": "-", "mul": "*", "div": "/",
        "andb": "&", "orb": "|", "xorb": "^"
    }
    cmp_syms = {
        "cmpeq": "==", "cmpneq": "!=", "cmplt": "<", "cmple": "<=", "cmpgt": ">", "cmpge": ">="
    }

    @property
    def name(self) -> str:
        return "obj"

    def format_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        if lmul_suffix and lmul_suffix not in ("", "m1", "m0"):
            coeff = lmul_suffix[1:] if lmul_suffix.startswith("m") else (f"-{lmul_suffix[1:]}" if lmul_suffix.startswith("d") else "1")
            return f"mipp::Rvd<T, {coeff}>"
        return "mipp::Rvd<T>"

    def format_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        if lmul_suffix and lmul_suffix not in ("", "m1", "m0"):
            coeff = lmul_suffix[1:] if lmul_suffix.startswith("m") else (f"-{lmul_suffix[1:]}" if lmul_suffix.startswith("d") else "1")
            return f"mipp::Rvm<T, {coeff}>"
        return "mipp::Rvm<T>"

    def format_scalar_reg_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return ""

    def format_scalar_msk_type(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return ""

    def format_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        return f"mipp::Rvd<T>({ptr_name})"

    def format_scalar_load(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        return ""

    def format_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        return f"mipp::Rvm<T>({ptr_name})"

    def format_scalar_set_k(self, dt_ext: str, ptr_name: str, lmul_suffix: str = "") -> str:
        return ""

    def format_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"{reg_name}[{index_expr}]"

    def format_scalar_get(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return ""

    def format_get_k(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return f"{reg_name}[{index_expr}]"

    def format_scalar_get_k(self, reg_name: str, index_expr: str, dt_ext: str, lmul_suffix: str = "") -> str:
        return ""

    def format_get_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    def format_scalar_get_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    def format_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        return f"{reg_name}.tomsk()"

    def format_scalar_tomsk(self, dt_ext: str, reg_name: str, lmul_suffix: str = "") -> str:
        return ""

    def format_get_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    def format_scalar_get_k_func_name(self, dt_ext: str, lmul_suffix: str = "") -> str:
        return "mipp::get"

    def format_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        parts = [p.strip() for p in args_str.split(",")]
        all_syms = {**self.op_syms, **self.cmp_syms}
        if func_name in all_syms and len(parts) == 2:
            return f"{parts[0]} {all_syms[func_name]} {parts[1]}"

        if len(parts) == 1:
            return f"{parts[0]}.{func_name}()"
        elif len(parts) >= 2:
            other_args = ", ".join(parts[1:])
            return f"{parts[0]}.{func_name}({other_args})"
        return f"{args_str}.{func_name}()"

    def format_scalar_func_call(self, func_name: str, dt_ext: str, args_str: str, lmul_suffix: str = "", mkind: str = "") -> str:
        return ""
