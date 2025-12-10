/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
    default_offprof.power_domains = 0;
    default_offprof.aon_clk_src = CLK_SRC_LFXO;
    default_offprof.dcdc_voltage = PM_DCDC_VOLTAGE;
    default_offprof.dcdc_mode = DCDC_MODE_PWM;
    default_offprof.stby_clk_src = CLK_SRC_HFRC;
    default_offprof.stby_clk_freq = SCALED_FREQ_RC_STDBY_38_4_MHZ;
    default_offprof.memory_blocks = SERAM_MASK | MRAM_MASK;
    default_offprof.ip_clock_gating = LP_PERIPH_MASK;
    default_offprof.phy_pwr_gating = 0;
    default_offprof.vdd_ioflex_3V3 = IOFLEX_LEVEL_1V8;
    default_offprof.wakeup_events = WE_LPGPIO | WE_LPTIMER;
    default_offprof.ewic_cfg = EWIC_VBAT_GPIO | EWIC_VBAT_TIMER;
#ifdef CORE_M55_HP
    default_offprof.vtor_address = 0x80200000;
    default_offprof.vtor_address_ns = 0x80200000;
#elif CORE_M55_HE
    default_offprof.vtor_address = 0x80000000;
    default_offprof.vtor_address_ns = 0x80000000;
#else
#error Unsupported core
#endif
