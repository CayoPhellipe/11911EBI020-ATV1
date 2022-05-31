#define SRAM_START 0x20000000U                /* Inicio da SRAM CORTEX-M */
#define SRAM_SIZE (128U * 1024U)              /* Tam. SRAM STM32F411 128K (STM32F411)*/
#define SRAM_END ((SRAM_START) + (SRAM_SIZE)) /* Final da SRAM STM32F411 */
#define STACK_START SRAM_END                  /* Inicio da Stack */
