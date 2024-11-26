/* Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#include <stdio.h>

#include "power_management.h"
#include "services_lib_api.h"
#include "services_lib_bare_metal.h"

#define PM_DCDC_VOLTAGE (825)

// SE handle
extern uint32_t se_services_s_handle;

void print_runprofile(const run_profile_t *runprof)
{
    printf("memory_blocks   %08X\n", runprof->memory_blocks);
    printf("power_domains   %08X\n", runprof->power_domains);
    printf("ip_clock_gating %08X\n", runprof->ip_clock_gating);
    printf("phy_pwr_gating  %08X\n", runprof->phy_pwr_gating);
    printf("vdd_ioflex_3V3  %08X\n", runprof->vdd_ioflex_3V3);
    printf("run_clk_src     %08X\n", runprof->run_clk_src);
    printf("aon_clk_src     %08X\n", runprof->aon_clk_src);
    printf("scaled_clk_freq %08X\n", runprof->scaled_clk_freq);
    printf("dcdc_mode       %08X\n", runprof->dcdc_mode);
    printf("dcdc_voltage    %u\n", runprof->dcdc_voltage);   
}

static bool set_power_profiles(void)
{
    run_profile_t default_runprof = {0};
    off_profile_t default_offprof = {0};

    uint32_t service_error_code;
    uint32_t err = 0;

    default_runprof.power_domains   = PD_VBAT_AON_MASK | PD_SSE700_AON_MASK | PD_SYST_MASK | PD_SESS_MASK;
    default_runprof.power_domains   |= PD_DBSS_MASK;// debug PD
    default_runprof.dcdc_mode       = DCDC_MODE_PWM;
    default_runprof.dcdc_voltage    = PM_DCDC_VOLTAGE;
    default_runprof.aon_clk_src     = CLK_SRC_LFXO;
    default_runprof.run_clk_src     = CLK_SRC_PLL;
    default_runprof.scaled_clk_freq = SCALED_FREQ_XO_HIGH_DIV_38_4_MHZ;
    default_runprof.memory_blocks   = SERAM_MASK | SRAM0_MASK | SRAM1_MASK | MRAM_MASK | FWRAM_MASK;
    default_runprof.ip_clock_gating = CAMERA_MASK | MIPI_DSI_MASK | MIPI_CSI_MASK | CDC200_MASK;
    default_runprof.phy_pwr_gating  = LDO_PHY_MASK | MIPI_TX_DPHY_MASK | MIPI_RX_DPHY_MASK | MIPI_PLL_DPHY_MASK;
    default_runprof.vdd_ioflex_3V3  = IOFLEX_LEVEL_1V8;

#ifdef CORE_M55_HP
    default_runprof.cpu_clk_freq    = CLOCK_FREQUENCY_400MHZ;
#elif CORE_M55_HE
    default_runprof.cpu_clk_freq    = CLOCK_FREQUENCY_160MHZ;
#else
#error Unsupported core
#endif

    err = SERVICES_set_run_cfg(se_services_s_handle, &default_runprof, &service_error_code);

    if (err == 0 && service_error_code == 0) {
        default_offprof.power_domains   = 0;
        default_offprof.aon_clk_src     = CLK_SRC_LFXO;
        default_offprof.dcdc_voltage    = PM_DCDC_VOLTAGE;
        default_offprof.dcdc_mode       = DCDC_MODE_PWM;
        default_offprof.stby_clk_src    = CLK_SRC_HFRC;
        default_offprof.stby_clk_freq   = SCALED_FREQ_RC_STDBY_38_4_MHZ;
        default_offprof.memory_blocks   = SERAM_MASK | MRAM_MASK;
        default_offprof.ip_clock_gating = LP_PERIPH_MASK;
        default_offprof.phy_pwr_gating  = 0;
        default_offprof.vdd_ioflex_3V3  = IOFLEX_LEVEL_1V8;
        default_offprof.wakeup_events   = WE_LPGPIO | WE_LPTIMER;
        default_offprof.ewic_cfg        = EWIC_VBAT_GPIO | EWIC_VBAT_TIMER;
#ifdef CORE_M55_HP
        default_offprof.vtor_address    = 0x80200000;
        default_offprof.vtor_address_ns = 0x80200000;
#elif CORE_M55_HE
        default_offprof.vtor_address    = 0x80000000;
        default_offprof.vtor_address_ns = 0x80000000;
#else
#error Unsupported core
#endif
        err = SERVICES_set_off_cfg(se_services_s_handle, &default_offprof, &service_error_code);
    }

    return err == 0 && service_error_code == 0;
}

bool init_power_management(void)
{
    SERVICES_synchronize_with_se(se_services_s_handle);
    return set_power_profiles();
}
