# Docker Images Generation

Build images:
```bash
cd linux/x86_64/gcc-14_clang-20
docker build -t linux_x86_64_gcc-14_clang-20 .
```

Create images aliases:
```bash
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:latest

docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse2
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse3
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_ssse3
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse4.1
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse4.2
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx2
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx2-fma
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx512f
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx512bw
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx512dq

docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse2
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse3
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_ssse3
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse4.1
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse4.2
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx2
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx2-fma
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx512f
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx512bw
docker tag linux_x86_64_gcc-14_clang-20 registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx512dq
```

Login to Gitlab.com registry:
```bash
docker login registry.gitlab.com -u {user_name} -p {password_or_token}
```

Push images to Gitlab.com:
```bash
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:latest

docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse2
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse3
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_ssse3
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse4.1
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_sse4.2
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx2
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx2-fma
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx512f
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx512bw
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:gcc-14_avx512dq

docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse2
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse3
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_ssse3
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse4.1
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_sse4.2
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx2
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx2-fma
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx512f
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx512bw
docker push registry.gitlab.com/aff3ct/aff3ct/mipp_linux:clang-20_avx512dq
```
