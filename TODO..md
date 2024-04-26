# TODO

- [ ] Add `compress` for NEONv1 with emulation of `vqtbl1q` based on two `vtbl2`
- [ ] Improve NEONv2 `shuff` operations with `vqtbl1q` instruction
- [ ] Create a docker image with "Intel Software Development Emulator" to enable 
      AVX-512 instructions emulation on the runners that does not support
      native AVX-512
- [ ] Find a workaround for the 16-bit SSE `compress` that requires BMI2 
      extension (remove `_pext_u32` dependency, available from Haswell)
