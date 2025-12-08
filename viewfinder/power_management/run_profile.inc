/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
    default_runprof.power_domains = PD_VBAT_AON_MASK | PD_SSE700_AON_MASK | PD_SYST_MASK | PD_SESS_MASK;
    default_runprof.power_domains |= PD_DBSS_MASK;  // debug PD
    default_runprof.dcdc_mode = DCDC_MODE_PWM;
    default_runprof.dcdc_voltage = PM_DCDC_VOLTAGE;
    default_runprof.aon_clk_src = CLK_SRC_LFXO;
    default_runprof.run_clk_src = CLK_SRC_PLL;
    default_runprof.scaled_clk_freq = SCALED_FREQ_XO_HIGH_DIV_38_4_MHZ;
    default_runprof.memory_blocks = SERAM_MASK | SRAM0_MASK | SRAM1_MASK | MRAM_MASK | FWRAM_MASK;
    default_runprof.ip_clock_gating = CAMERA_MASK | MIPI_DSI_MASK | MIPI_CSI_MASK | CDC200_MASK | GPU_MASK;
    default_runprof.phy_pwr_gating = LDO_PHY_MASK | MIPI_TX_DPHY_MASK | MIPI_RX_DPHY_MASK | MIPI_PLL_DPHY_MASK;
    default_runprof.vdd_ioflex_3V3 = IOFLEX_LEVEL_1V8;
#ifdef CORE_M55_HP
    default_runprof.cpu_clk_freq = CLOCK_FREQUENCY_400MHZ;
#elif CORE_M55_HE
    default_runprof.cpu_clk_freq = CLOCK_FREQUENCY_160MHZ;
#else
#error Unsupported core
#endif