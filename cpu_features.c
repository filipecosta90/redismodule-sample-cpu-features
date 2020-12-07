#include "redismodule.h"
#include <stdbool.h>
#include <string.h>

#include "cpu_features_macros.h"

#define CPU_FEATURES_TRUE -1
#if defined(CPU_FEATURES_ARCH_X86)
#include "cpuinfo_x86.h"
int compiled_avx = CPU_FEATURES_COMPILED_X86_AVX;
int compiled_avx2 = CPU_FEATURES_COMPILED_X86_AVX2;
#elif defined(CPU_FEATURES_ARCH_ARM)
#include "cpuinfo_arm.h"
// TODO: add logic for arch

#elif defined(CPU_FEATURES_ARCH_AARCH64)
#include "cpuinfo_aarch64.h"
// TODO: add logic for arch

#elif defined(CPU_FEATURES_ARCH_MIPS)
#include "cpuinfo_mips.h"
// TODO: add logic for arch

#elif defined(CPU_FEATURES_ARCH_PPC)
#include "cpuinfo_ppc.h"
// TODO: add logic for arch

#endif

/* CPU.SUBSTRING ABCD ABCD_ABC_ABCD_AB
 */
int SubStringCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

  // we must have at least 3 args
  if (argc < 3) {
    return RedisModule_WrongArity(ctx);
  }

  const char *needle = RedisModule_StringPtrLen(argv[1], NULL);
  const char *haystack = RedisModule_StringPtrLen(argv[2], NULL);
  char *ret;

  ret = strstr(haystack, needle);

  // ret logic ...
  return RedisModule_ReplyWithCString(ctx, "OK");
}

static void log_warn_instruction_set_extensions(RedisModuleCtx *ctx,
                                                const char *extension) {
  RedisModule_Log(
      ctx, "warning",
      "The module wasn't compiled to use %s instructions, but these are "
      "available on your machine and could speed up CPU computations.",
      extension);
}

int RedisModule_OnLoad(RedisModuleCtx *ctx) {

  // Register the module itself
  if (RedisModule_Init(ctx, "sample_cpu_features", 1, REDISMODULE_APIVER_1) ==
      REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }
#if defined(CPU_FEATURES_ARCH_X86)
  X86Info info = GetX86Info();

  if (info.features.avx2 == CPU_FEATURES_TRUE && compiled_avx2 == 0) {
    log_warn_instruction_set_extensions(ctx, "AVX2");
  }
  if (info.features.avx == CPU_FEATURES_TRUE && compiled_avx == 0) {
    log_warn_instruction_set_extensions(ctx, "AVX");
  }
#elif defined(CPU_FEATURES_ARCH_ARM)
#endif

  if (info.features.avx2 == CPU_FEATURES_TRUE && compiled_avx2 == 1) {

  } else {
    // fallback to default implementation
    // register CPU.SUBSTRING
    if (RedisModule_CreateCommand(ctx, "CPU.SUBSTRING", SubStringCommand,
                                  "readonly", 1, 1, 1) == REDISMODULE_ERR) {
      return REDISMODULE_ERR;
    }
  }

  return REDISMODULE_OK;
}