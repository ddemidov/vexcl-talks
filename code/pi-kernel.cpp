#if defined(cl_khr_fp64)
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#elif defined(cl_amd_fp64)
#pragma OPENCL EXTENSION cl_amd_fp64: enable
#endif

void philox_uint_4_10
(
  uint * ctr,
  uint * key
)
{
  uint m[4];
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
  key[0] += 0x9E3779B9;
  key[1] += 0xBB67AE85;
  m[0] = mul_hi(0xD2511F53, ctr[0]);
  m[1] = 0xD2511F53 * ctr[0];
  m[2] = mul_hi(0xCD9E8D57, ctr[2]);
  m[3] = 0xCD9E8D57 * ctr[2];
  ctr[0] = m[2] ^ ctr[1] ^ key[0];
  ctr[1] = m[3];
  ctr[2] = m[0] ^ ctr[3] ^ key[1];
  ctr[3] = m[1];
}

double2 random_double2_philox
(
  ulong prm1,
  ulong prm2
)
{
  union 
  {
    uint ctr[4];
    ulong res_i[2];
    double res_f[2];
    double2 res;
  } ctr;
  uint key[2];
  ctr.ctr[0] = prm1; ctr.ctr[1] = prm2;
  ctr.ctr[2] = prm1; ctr.ctr[3] = prm2;
  key[0] = 0x12345678;
  key[1] = 0x12345678;
  philox_uint_4_10(ctr.ctr, key);
  ctr.res_f[0] = ctr.res_i[0] / 18446744073709551615.0;
  ctr.res_f[1] = ctr.res_i[1] / 18446744073709551615.0;
  return ctr.res;
}

ulong SUM_ulong
(
  ulong prm1,
  ulong prm2
)
{
  return prm1 + prm2;
}

kernel void vexcl_reductor_kernel
(
  ulong n,
  ulong prm_1,
  ulong prm_2,
  double prm_3,
  global ulong * g_odata,
  local ulong * smem
)
{
  ulong mySum = (ulong)0;
  for(ulong idx = get_global_id(0); idx < n; idx += get_global_size(0))
  {
    mySum = SUM_ulong(mySum,
            ( length( random_double2_philox( (prm_1 + idx), prm_2 ) ) < prm_3 ));
  }

  local ulong * sdata = smem;
  size_t tid = get_local_id(0);
  size_t block_size = get_local_size(0);
  sdata[tid] = mySum;
  barrier(CLK_LOCAL_MEM_FENCE);
  if (block_size >= 1024)
  {
    if (tid < 512) { sdata[tid] = mySum = SUM_ulong(mySum, sdata[tid + 512]); }
    barrier(CLK_LOCAL_MEM_FENCE);
  }
  if (block_size >= 512)
  {
    if (tid < 256) { sdata[tid] = mySum = SUM_ulong(mySum, sdata[tid + 256]); }
    barrier(CLK_LOCAL_MEM_FENCE);
  }
  if (block_size >= 256)
  {
    if (tid < 128) { sdata[tid] = mySum = SUM_ulong(mySum, sdata[tid + 128]); }
    barrier(CLK_LOCAL_MEM_FENCE);
  }
  if (block_size >= 128)
  {
    if (tid < 64) { sdata[tid] = mySum = SUM_ulong(mySum, sdata[tid + 64]); }
    barrier(CLK_LOCAL_MEM_FENCE);
  }
  if (tid < 32)
  {
    volatile local ulong * smem = sdata;
    if (block_size >= 64) { smem[tid] = mySum = SUM_ulong(mySum, smem[tid + 32]); }
    if (block_size >= 32) { smem[tid] = mySum = SUM_ulong(mySum, smem[tid + 16]); }
    if (block_size >= 16) { smem[tid] = mySum = SUM_ulong(mySum, smem[tid + 8]); }
    if (block_size >= 8) { smem[tid] = mySum = SUM_ulong(mySum, smem[tid + 4]); }
    if (block_size >= 4) { smem[tid] = mySum = SUM_ulong(mySum, smem[tid + 2]); }
    if (block_size >= 2) { smem[tid] = mySum = SUM_ulong(mySum, smem[tid + 1]); }
  }
  if (tid == 0) g_odata[get_group_id(0)] = sdata[0];
}
