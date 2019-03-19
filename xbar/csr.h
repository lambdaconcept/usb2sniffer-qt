#ifndef __GENERATED_CSR_H
#define __GENERATED_CSR_H
#include <stdint.h>
#ifdef CSR_ACCESSORS_DEFINED
extern void csr_writeb(uint8_t value, uint32_t addr);
extern uint8_t csr_readb(uint32_t addr);
extern void csr_writew(uint16_t value, uint32_t addr);
extern uint16_t csr_readw(uint32_t addr);
extern void csr_writel(uint32_t value, uint32_t addr);
extern uint32_t csr_readl(uint32_t addr);
#else /* ! CSR_ACCESSORS_DEFINED */
#include <hw/common.h>
#endif /* ! CSR_ACCESSORS_DEFINED */

/* blinker0 */
#define CSR_BLINKER0_BASE 0xe000b000
#define CSR_BLINKER0_FORCEBLINK_ADDR 0xe000b000
#define CSR_BLINKER0_FORCEBLINK_SIZE 1
static inline unsigned int blinker0_forceblink_read(void) {
	unsigned int r = csr_readl(0xe000b000);
	return r;
}
static inline void blinker0_forceblink_write(unsigned int value) {
	csr_writel(value, 0xe000b000);
}

/* blinker1 */
#define CSR_BLINKER1_BASE 0xe000b800
#define CSR_BLINKER1_FORCEBLINK_ADDR 0xe000b800
#define CSR_BLINKER1_FORCEBLINK_SIZE 1
static inline unsigned int blinker1_forceblink_read(void) {
	unsigned int r = csr_readl(0xe000b800);
	return r;
}
static inline void blinker1_forceblink_write(unsigned int value) {
	csr_writel(value, 0xe000b800);
}

/* ctrl */
#define CSR_CTRL_BASE 0xe0000000
#define CSR_CTRL_RESET_ADDR 0xe0000000
#define CSR_CTRL_RESET_SIZE 1
static inline unsigned int ctrl_reset_read(void) {
	unsigned int r = csr_readl(0xe0000000);
	return r;
}
static inline void ctrl_reset_write(unsigned int value) {
	csr_writel(value, 0xe0000000);
}
#define CSR_CTRL_SCRATCH_ADDR 0xe0000004
#define CSR_CTRL_SCRATCH_SIZE 1
static inline unsigned int ctrl_scratch_read(void) {
	unsigned int r = csr_readl(0xe0000004);
	return r;
}
static inline void ctrl_scratch_write(unsigned int value) {
	csr_writel(value, 0xe0000004);
}
#define CSR_CTRL_BUS_ERRORS_ADDR 0xe0000008
#define CSR_CTRL_BUS_ERRORS_SIZE 1
static inline unsigned int ctrl_bus_errors_read(void) {
	unsigned int r = csr_readl(0xe0000008);
	return r;
}

/* ddrphy */
#define CSR_DDRPHY_BASE 0xe0005800
#define CSR_DDRPHY_HALF_SYS8X_TAPS_ADDR 0xe0005800
#define CSR_DDRPHY_HALF_SYS8X_TAPS_SIZE 1
static inline unsigned int ddrphy_half_sys8x_taps_read(void) {
	unsigned int r = csr_readl(0xe0005800);
	return r;
}
static inline void ddrphy_half_sys8x_taps_write(unsigned int value) {
	csr_writel(value, 0xe0005800);
}
#define CSR_DDRPHY_CDLY_RST_ADDR 0xe0005804
#define CSR_DDRPHY_CDLY_RST_SIZE 1
static inline unsigned int ddrphy_cdly_rst_read(void) {
	unsigned int r = csr_readl(0xe0005804);
	return r;
}
static inline void ddrphy_cdly_rst_write(unsigned int value) {
	csr_writel(value, 0xe0005804);
}
#define CSR_DDRPHY_CDLY_INC_ADDR 0xe0005808
#define CSR_DDRPHY_CDLY_INC_SIZE 1
static inline unsigned int ddrphy_cdly_inc_read(void) {
	unsigned int r = csr_readl(0xe0005808);
	return r;
}
static inline void ddrphy_cdly_inc_write(unsigned int value) {
	csr_writel(value, 0xe0005808);
}
#define CSR_DDRPHY_DLY_SEL_ADDR 0xe000580c
#define CSR_DDRPHY_DLY_SEL_SIZE 1
static inline unsigned int ddrphy_dly_sel_read(void) {
	unsigned int r = csr_readl(0xe000580c);
	return r;
}
static inline void ddrphy_dly_sel_write(unsigned int value) {
	csr_writel(value, 0xe000580c);
}
#define CSR_DDRPHY_RDLY_DQ_RST_ADDR 0xe0005810
#define CSR_DDRPHY_RDLY_DQ_RST_SIZE 1
static inline unsigned int ddrphy_rdly_dq_rst_read(void) {
	unsigned int r = csr_readl(0xe0005810);
	return r;
}
static inline void ddrphy_rdly_dq_rst_write(unsigned int value) {
	csr_writel(value, 0xe0005810);
}
#define CSR_DDRPHY_RDLY_DQ_INC_ADDR 0xe0005814
#define CSR_DDRPHY_RDLY_DQ_INC_SIZE 1
static inline unsigned int ddrphy_rdly_dq_inc_read(void) {
	unsigned int r = csr_readl(0xe0005814);
	return r;
}
static inline void ddrphy_rdly_dq_inc_write(unsigned int value) {
	csr_writel(value, 0xe0005814);
}
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_RST_ADDR 0xe0005818
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_RST_SIZE 1
static inline unsigned int ddrphy_rdly_dq_bitslip_rst_read(void) {
	unsigned int r = csr_readl(0xe0005818);
	return r;
}
static inline void ddrphy_rdly_dq_bitslip_rst_write(unsigned int value) {
	csr_writel(value, 0xe0005818);
}
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_ADDR 0xe000581c
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_SIZE 1
static inline unsigned int ddrphy_rdly_dq_bitslip_read(void) {
	unsigned int r = csr_readl(0xe000581c);
	return r;
}
static inline void ddrphy_rdly_dq_bitslip_write(unsigned int value) {
	csr_writel(value, 0xe000581c);
}

/* flash */
#define CSR_FLASH_BASE 0xe0005000
#define CSR_FLASH_SPI_CTRL_ADDR 0xe0005000
#define CSR_FLASH_SPI_CTRL_SIZE 1
static inline unsigned int flash_spi_ctrl_read(void) {
	unsigned int r = csr_readl(0xe0005000);
	return r;
}
static inline void flash_spi_ctrl_write(unsigned int value) {
	csr_writel(value, 0xe0005000);
}
#define CSR_FLASH_SPI_STATUS_ADDR 0xe0005004
#define CSR_FLASH_SPI_STATUS_SIZE 1
static inline unsigned int flash_spi_status_read(void) {
	unsigned int r = csr_readl(0xe0005004);
	return r;
}
#define CSR_FLASH_SPI_MOSI_ADDR 0xe0005008
#define CSR_FLASH_SPI_MOSI_SIZE 2
static inline unsigned long long int flash_spi_mosi_read(void) {
	unsigned long long int r = csr_readl(0xe0005008);
	r <<= 32;
	r |= csr_readl(0xe000500c);
	return r;
}
static inline void flash_spi_mosi_write(unsigned long long int value) {
	csr_writel(value >> 32, 0xe0005008);
	csr_writel(value, 0xe000500c);
}
#define CSR_FLASH_SPI_MISO_ADDR 0xe0005010
#define CSR_FLASH_SPI_MISO_SIZE 2
static inline unsigned long long int flash_spi_miso_read(void) {
	unsigned long long int r = csr_readl(0xe0005010);
	r <<= 32;
	r |= csr_readl(0xe0005014);
	return r;
}

/* iticore0 */
#define CSR_ITICORE0_BASE 0xe000a000
#define CSR_ITICORE0_START_PATTERN_ADDR 0xe000a000
#define CSR_ITICORE0_START_PATTERN_SIZE 1
static inline unsigned int iticore0_start_pattern_read(void) {
	unsigned int r = csr_readl(0xe000a000);
	return r;
}
static inline void iticore0_start_pattern_write(unsigned int value) {
	csr_writel(value, 0xe000a000);
}
#define CSR_ITICORE0_PACKER_TIME_ENABLE_ADDR 0xe000a004
#define CSR_ITICORE0_PACKER_TIME_ENABLE_SIZE 1
static inline unsigned int iticore0_packer_time_enable_read(void) {
	unsigned int r = csr_readl(0xe000a004);
	return r;
}
static inline void iticore0_packer_time_enable_write(unsigned int value) {
	csr_writel(value, 0xe000a004);
}
#define CSR_ITICORE0_PACKER_EV_EVENT_ADDR 0xe000a008
#define CSR_ITICORE0_PACKER_EV_EVENT_SIZE 1
static inline unsigned int iticore0_packer_ev_event_read(void) {
	unsigned int r = csr_readl(0xe000a008);
	return r;
}
static inline void iticore0_packer_ev_event_write(unsigned int value) {
	csr_writel(value, 0xe000a008);
}

/* overflow0 */
#define CSR_OVERFLOW0_BASE 0xe0008000
#define CSR_OVERFLOW0_RESET_ADDR 0xe0008000
#define CSR_OVERFLOW0_RESET_SIZE 1
static inline unsigned int overflow0_reset_read(void) {
	unsigned int r = csr_readl(0xe0008000);
	return r;
}
static inline void overflow0_reset_write(unsigned int value) {
	csr_writel(value, 0xe0008000);
}
#define CSR_OVERFLOW0_COUNT_ADDR 0xe0008004
#define CSR_OVERFLOW0_COUNT_SIZE 1
static inline unsigned int overflow0_count_read(void) {
	unsigned int r = csr_readl(0xe0008004);
	return r;
}

/* rst_manager */
#define CSR_RST_MANAGER_BASE 0xe000c000
#define CSR_RST_MANAGER_RESET_ADDR 0xe000c000
#define CSR_RST_MANAGER_RESET_SIZE 1
static inline unsigned int rst_manager_reset_read(void) {
	unsigned int r = csr_readl(0xe000c000);
	return r;
}
static inline void rst_manager_reset_write(unsigned int value) {
	csr_writel(value, 0xe000c000);
}

/* sdram */
#define CSR_SDRAM_BASE 0xe0004000
#define CSR_SDRAM_DFII_CONTROL_ADDR 0xe0004000
#define CSR_SDRAM_DFII_CONTROL_SIZE 1
static inline unsigned int sdram_dfii_control_read(void) {
	unsigned int r = csr_readl(0xe0004000);
	return r;
}
static inline void sdram_dfii_control_write(unsigned int value) {
	csr_writel(value, 0xe0004000);
}
#define CSR_SDRAM_DFII_PI0_COMMAND_ADDR 0xe0004004
#define CSR_SDRAM_DFII_PI0_COMMAND_SIZE 1
static inline unsigned int sdram_dfii_pi0_command_read(void) {
	unsigned int r = csr_readl(0xe0004004);
	return r;
}
static inline void sdram_dfii_pi0_command_write(unsigned int value) {
	csr_writel(value, 0xe0004004);
}
#define CSR_SDRAM_DFII_PI0_COMMAND_ISSUE_ADDR 0xe0004008
#define CSR_SDRAM_DFII_PI0_COMMAND_ISSUE_SIZE 1
static inline unsigned int sdram_dfii_pi0_command_issue_read(void) {
	unsigned int r = csr_readl(0xe0004008);
	return r;
}
static inline void sdram_dfii_pi0_command_issue_write(unsigned int value) {
	csr_writel(value, 0xe0004008);
}
#define CSR_SDRAM_DFII_PI0_ADDRESS_ADDR 0xe000400c
#define CSR_SDRAM_DFII_PI0_ADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi0_address_read(void) {
	unsigned int r = csr_readl(0xe000400c);
	return r;
}
static inline void sdram_dfii_pi0_address_write(unsigned int value) {
	csr_writel(value, 0xe000400c);
}
#define CSR_SDRAM_DFII_PI0_BADDRESS_ADDR 0xe0004010
#define CSR_SDRAM_DFII_PI0_BADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi0_baddress_read(void) {
	unsigned int r = csr_readl(0xe0004010);
	return r;
}
static inline void sdram_dfii_pi0_baddress_write(unsigned int value) {
	csr_writel(value, 0xe0004010);
}
#define CSR_SDRAM_DFII_PI0_WRDATA_ADDR 0xe0004014
#define CSR_SDRAM_DFII_PI0_WRDATA_SIZE 1
static inline unsigned int sdram_dfii_pi0_wrdata_read(void) {
	unsigned int r = csr_readl(0xe0004014);
	return r;
}
static inline void sdram_dfii_pi0_wrdata_write(unsigned int value) {
	csr_writel(value, 0xe0004014);
}
#define CSR_SDRAM_DFII_PI0_RDDATA_ADDR 0xe0004018
#define CSR_SDRAM_DFII_PI0_RDDATA_SIZE 1
static inline unsigned int sdram_dfii_pi0_rddata_read(void) {
	unsigned int r = csr_readl(0xe0004018);
	return r;
}
#define CSR_SDRAM_DFII_PI1_COMMAND_ADDR 0xe000401c
#define CSR_SDRAM_DFII_PI1_COMMAND_SIZE 1
static inline unsigned int sdram_dfii_pi1_command_read(void) {
	unsigned int r = csr_readl(0xe000401c);
	return r;
}
static inline void sdram_dfii_pi1_command_write(unsigned int value) {
	csr_writel(value, 0xe000401c);
}
#define CSR_SDRAM_DFII_PI1_COMMAND_ISSUE_ADDR 0xe0004020
#define CSR_SDRAM_DFII_PI1_COMMAND_ISSUE_SIZE 1
static inline unsigned int sdram_dfii_pi1_command_issue_read(void) {
	unsigned int r = csr_readl(0xe0004020);
	return r;
}
static inline void sdram_dfii_pi1_command_issue_write(unsigned int value) {
	csr_writel(value, 0xe0004020);
}
#define CSR_SDRAM_DFII_PI1_ADDRESS_ADDR 0xe0004024
#define CSR_SDRAM_DFII_PI1_ADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi1_address_read(void) {
	unsigned int r = csr_readl(0xe0004024);
	return r;
}
static inline void sdram_dfii_pi1_address_write(unsigned int value) {
	csr_writel(value, 0xe0004024);
}
#define CSR_SDRAM_DFII_PI1_BADDRESS_ADDR 0xe0004028
#define CSR_SDRAM_DFII_PI1_BADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi1_baddress_read(void) {
	unsigned int r = csr_readl(0xe0004028);
	return r;
}
static inline void sdram_dfii_pi1_baddress_write(unsigned int value) {
	csr_writel(value, 0xe0004028);
}
#define CSR_SDRAM_DFII_PI1_WRDATA_ADDR 0xe000402c
#define CSR_SDRAM_DFII_PI1_WRDATA_SIZE 1
static inline unsigned int sdram_dfii_pi1_wrdata_read(void) {
	unsigned int r = csr_readl(0xe000402c);
	return r;
}
static inline void sdram_dfii_pi1_wrdata_write(unsigned int value) {
	csr_writel(value, 0xe000402c);
}
#define CSR_SDRAM_DFII_PI1_RDDATA_ADDR 0xe0004030
#define CSR_SDRAM_DFII_PI1_RDDATA_SIZE 1
static inline unsigned int sdram_dfii_pi1_rddata_read(void) {
	unsigned int r = csr_readl(0xe0004030);
	return r;
}
#define CSR_SDRAM_DFII_PI2_COMMAND_ADDR 0xe0004034
#define CSR_SDRAM_DFII_PI2_COMMAND_SIZE 1
static inline unsigned int sdram_dfii_pi2_command_read(void) {
	unsigned int r = csr_readl(0xe0004034);
	return r;
}
static inline void sdram_dfii_pi2_command_write(unsigned int value) {
	csr_writel(value, 0xe0004034);
}
#define CSR_SDRAM_DFII_PI2_COMMAND_ISSUE_ADDR 0xe0004038
#define CSR_SDRAM_DFII_PI2_COMMAND_ISSUE_SIZE 1
static inline unsigned int sdram_dfii_pi2_command_issue_read(void) {
	unsigned int r = csr_readl(0xe0004038);
	return r;
}
static inline void sdram_dfii_pi2_command_issue_write(unsigned int value) {
	csr_writel(value, 0xe0004038);
}
#define CSR_SDRAM_DFII_PI2_ADDRESS_ADDR 0xe000403c
#define CSR_SDRAM_DFII_PI2_ADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi2_address_read(void) {
	unsigned int r = csr_readl(0xe000403c);
	return r;
}
static inline void sdram_dfii_pi2_address_write(unsigned int value) {
	csr_writel(value, 0xe000403c);
}
#define CSR_SDRAM_DFII_PI2_BADDRESS_ADDR 0xe0004040
#define CSR_SDRAM_DFII_PI2_BADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi2_baddress_read(void) {
	unsigned int r = csr_readl(0xe0004040);
	return r;
}
static inline void sdram_dfii_pi2_baddress_write(unsigned int value) {
	csr_writel(value, 0xe0004040);
}
#define CSR_SDRAM_DFII_PI2_WRDATA_ADDR 0xe0004044
#define CSR_SDRAM_DFII_PI2_WRDATA_SIZE 1
static inline unsigned int sdram_dfii_pi2_wrdata_read(void) {
	unsigned int r = csr_readl(0xe0004044);
	return r;
}
static inline void sdram_dfii_pi2_wrdata_write(unsigned int value) {
	csr_writel(value, 0xe0004044);
}
#define CSR_SDRAM_DFII_PI2_RDDATA_ADDR 0xe0004048
#define CSR_SDRAM_DFII_PI2_RDDATA_SIZE 1
static inline unsigned int sdram_dfii_pi2_rddata_read(void) {
	unsigned int r = csr_readl(0xe0004048);
	return r;
}
#define CSR_SDRAM_DFII_PI3_COMMAND_ADDR 0xe000404c
#define CSR_SDRAM_DFII_PI3_COMMAND_SIZE 1
static inline unsigned int sdram_dfii_pi3_command_read(void) {
	unsigned int r = csr_readl(0xe000404c);
	return r;
}
static inline void sdram_dfii_pi3_command_write(unsigned int value) {
	csr_writel(value, 0xe000404c);
}
#define CSR_SDRAM_DFII_PI3_COMMAND_ISSUE_ADDR 0xe0004050
#define CSR_SDRAM_DFII_PI3_COMMAND_ISSUE_SIZE 1
static inline unsigned int sdram_dfii_pi3_command_issue_read(void) {
	unsigned int r = csr_readl(0xe0004050);
	return r;
}
static inline void sdram_dfii_pi3_command_issue_write(unsigned int value) {
	csr_writel(value, 0xe0004050);
}
#define CSR_SDRAM_DFII_PI3_ADDRESS_ADDR 0xe0004054
#define CSR_SDRAM_DFII_PI3_ADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi3_address_read(void) {
	unsigned int r = csr_readl(0xe0004054);
	return r;
}
static inline void sdram_dfii_pi3_address_write(unsigned int value) {
	csr_writel(value, 0xe0004054);
}
#define CSR_SDRAM_DFII_PI3_BADDRESS_ADDR 0xe0004058
#define CSR_SDRAM_DFII_PI3_BADDRESS_SIZE 1
static inline unsigned int sdram_dfii_pi3_baddress_read(void) {
	unsigned int r = csr_readl(0xe0004058);
	return r;
}
static inline void sdram_dfii_pi3_baddress_write(unsigned int value) {
	csr_writel(value, 0xe0004058);
}
#define CSR_SDRAM_DFII_PI3_WRDATA_ADDR 0xe000405c
#define CSR_SDRAM_DFII_PI3_WRDATA_SIZE 1
static inline unsigned int sdram_dfii_pi3_wrdata_read(void) {
	unsigned int r = csr_readl(0xe000405c);
	return r;
}
static inline void sdram_dfii_pi3_wrdata_write(unsigned int value) {
	csr_writel(value, 0xe000405c);
}
#define CSR_SDRAM_DFII_PI3_RDDATA_ADDR 0xe0004060
#define CSR_SDRAM_DFII_PI3_RDDATA_SIZE 1
static inline unsigned int sdram_dfii_pi3_rddata_read(void) {
	unsigned int r = csr_readl(0xe0004060);
	return r;
}

/* ulpi_core0 */
#define CSR_ULPI_CORE0_BASE 0xe0007000
#define CSR_ULPI_CORE0_REG_ADR_ADDR 0xe0007000
#define CSR_ULPI_CORE0_REG_ADR_SIZE 1
static inline unsigned int ulpi_core0_reg_adr_read(void) {
	unsigned int r = csr_readl(0xe0007000);
	return r;
}
static inline void ulpi_core0_reg_adr_write(unsigned int value) {
	csr_writel(value, 0xe0007000);
}
#define CSR_ULPI_CORE0_REG_DAT_R_ADDR 0xe0007004
#define CSR_ULPI_CORE0_REG_DAT_R_SIZE 1
static inline unsigned int ulpi_core0_reg_dat_r_read(void) {
	unsigned int r = csr_readl(0xe0007004);
	return r;
}
#define CSR_ULPI_CORE0_REG_DAT_W_ADDR 0xe0007008
#define CSR_ULPI_CORE0_REG_DAT_W_SIZE 1
static inline unsigned int ulpi_core0_reg_dat_w_read(void) {
	unsigned int r = csr_readl(0xe0007008);
	return r;
}
static inline void ulpi_core0_reg_dat_w_write(unsigned int value) {
	csr_writel(value, 0xe0007008);
}
#define CSR_ULPI_CORE0_REG_WRITE_ADDR 0xe000700c
#define CSR_ULPI_CORE0_REG_WRITE_SIZE 1
static inline unsigned int ulpi_core0_reg_write_read(void) {
	unsigned int r = csr_readl(0xe000700c);
	return r;
}
static inline void ulpi_core0_reg_write_write(unsigned int value) {
	csr_writel(value, 0xe000700c);
}
#define CSR_ULPI_CORE0_REG_READ_ADDR 0xe0007010
#define CSR_ULPI_CORE0_REG_READ_SIZE 1
static inline unsigned int ulpi_core0_reg_read_read(void) {
	unsigned int r = csr_readl(0xe0007010);
	return r;
}
static inline void ulpi_core0_reg_read_write(unsigned int value) {
	csr_writel(value, 0xe0007010);
}
#define CSR_ULPI_CORE0_REG_DONE_ADDR 0xe0007014
#define CSR_ULPI_CORE0_REG_DONE_SIZE 1
static inline unsigned int ulpi_core0_reg_done_read(void) {
	unsigned int r = csr_readl(0xe0007014);
	return r;
}
#define CSR_ULPI_CORE0_ENABLE_SOURCE_ADDR 0xe0007018
#define CSR_ULPI_CORE0_ENABLE_SOURCE_SIZE 1
static inline unsigned int ulpi_core0_enable_source_read(void) {
	unsigned int r = csr_readl(0xe0007018);
	return r;
}
static inline void ulpi_core0_enable_source_write(unsigned int value) {
	csr_writel(value, 0xe0007018);
}

/* ulpi_core1 */
#define CSR_ULPI_CORE1_BASE 0xe0007800
#define CSR_ULPI_CORE1_REG_ADR_ADDR 0xe0007800
#define CSR_ULPI_CORE1_REG_ADR_SIZE 1
static inline unsigned int ulpi_core1_reg_adr_read(void) {
	unsigned int r = csr_readl(0xe0007800);
	return r;
}
static inline void ulpi_core1_reg_adr_write(unsigned int value) {
	csr_writel(value, 0xe0007800);
}
#define CSR_ULPI_CORE1_REG_DAT_R_ADDR 0xe0007804
#define CSR_ULPI_CORE1_REG_DAT_R_SIZE 1
static inline unsigned int ulpi_core1_reg_dat_r_read(void) {
	unsigned int r = csr_readl(0xe0007804);
	return r;
}
#define CSR_ULPI_CORE1_REG_DAT_W_ADDR 0xe0007808
#define CSR_ULPI_CORE1_REG_DAT_W_SIZE 1
static inline unsigned int ulpi_core1_reg_dat_w_read(void) {
	unsigned int r = csr_readl(0xe0007808);
	return r;
}
static inline void ulpi_core1_reg_dat_w_write(unsigned int value) {
	csr_writel(value, 0xe0007808);
}
#define CSR_ULPI_CORE1_REG_WRITE_ADDR 0xe000780c
#define CSR_ULPI_CORE1_REG_WRITE_SIZE 1
static inline unsigned int ulpi_core1_reg_write_read(void) {
	unsigned int r = csr_readl(0xe000780c);
	return r;
}
static inline void ulpi_core1_reg_write_write(unsigned int value) {
	csr_writel(value, 0xe000780c);
}
#define CSR_ULPI_CORE1_REG_READ_ADDR 0xe0007810
#define CSR_ULPI_CORE1_REG_READ_SIZE 1
static inline unsigned int ulpi_core1_reg_read_read(void) {
	unsigned int r = csr_readl(0xe0007810);
	return r;
}
static inline void ulpi_core1_reg_read_write(unsigned int value) {
	csr_writel(value, 0xe0007810);
}
#define CSR_ULPI_CORE1_REG_DONE_ADDR 0xe0007814
#define CSR_ULPI_CORE1_REG_DONE_SIZE 1
static inline unsigned int ulpi_core1_reg_done_read(void) {
	unsigned int r = csr_readl(0xe0007814);
	return r;
}
#define CSR_ULPI_CORE1_ENABLE_SOURCE_ADDR 0xe0007818
#define CSR_ULPI_CORE1_ENABLE_SOURCE_SIZE 1
static inline unsigned int ulpi_core1_enable_source_read(void) {
	unsigned int r = csr_readl(0xe0007818);
	return r;
}
static inline void ulpi_core1_enable_source_write(unsigned int value) {
	csr_writel(value, 0xe0007818);
}

/* ulpi_phy0 */
#define CSR_ULPI_PHY0_BASE 0xe0006000
#define CSR_ULPI_PHY0_ULPI_PHY_RESET_ADDR 0xe0006000
#define CSR_ULPI_PHY0_ULPI_PHY_RESET_SIZE 1
static inline unsigned int ulpi_phy0_ulpi_phy_reset_read(void) {
	unsigned int r = csr_readl(0xe0006000);
	return r;
}
static inline void ulpi_phy0_ulpi_phy_reset_write(unsigned int value) {
	csr_writel(value, 0xe0006000);
}
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_RESET_ADDR 0xe0006004
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_RESET_SIZE 1
static inline unsigned int ulpi_phy0_ulpi_phy_rx_count_reset_read(void) {
	unsigned int r = csr_readl(0xe0006004);
	return r;
}
static inline void ulpi_phy0_ulpi_phy_rx_count_reset_write(unsigned int value) {
	csr_writel(value, 0xe0006004);
}
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_ADDR 0xe0006008
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_SIZE 1
static inline unsigned int ulpi_phy0_ulpi_phy_rx_count_read(void) {
	unsigned int r = csr_readl(0xe0006008);
	return r;
}
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_RESET_ADDR 0xe000600c
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_RESET_SIZE 1
static inline unsigned int ulpi_phy0_ulpi_phy_tx_count_reset_read(void) {
	unsigned int r = csr_readl(0xe000600c);
	return r;
}
static inline void ulpi_phy0_ulpi_phy_tx_count_reset_write(unsigned int value) {
	csr_writel(value, 0xe000600c);
}
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_ADDR 0xe0006010
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_SIZE 1
static inline unsigned int ulpi_phy0_ulpi_phy_tx_count_read(void) {
	unsigned int r = csr_readl(0xe0006010);
	return r;
}

/* ulpi_phy1 */
#define CSR_ULPI_PHY1_BASE 0xe0006800
#define CSR_ULPI_PHY1_ULPI_PHY_RESET_ADDR 0xe0006800
#define CSR_ULPI_PHY1_ULPI_PHY_RESET_SIZE 1
static inline unsigned int ulpi_phy1_ulpi_phy_reset_read(void) {
	unsigned int r = csr_readl(0xe0006800);
	return r;
}
static inline void ulpi_phy1_ulpi_phy_reset_write(unsigned int value) {
	csr_writel(value, 0xe0006800);
}
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_RESET_ADDR 0xe0006804
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_RESET_SIZE 1
static inline unsigned int ulpi_phy1_ulpi_phy_rx_count_reset_read(void) {
	unsigned int r = csr_readl(0xe0006804);
	return r;
}
static inline void ulpi_phy1_ulpi_phy_rx_count_reset_write(unsigned int value) {
	csr_writel(value, 0xe0006804);
}
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_ADDR 0xe0006808
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_SIZE 1
static inline unsigned int ulpi_phy1_ulpi_phy_rx_count_read(void) {
	unsigned int r = csr_readl(0xe0006808);
	return r;
}
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_RESET_ADDR 0xe000680c
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_RESET_SIZE 1
static inline unsigned int ulpi_phy1_ulpi_phy_tx_count_reset_read(void) {
	unsigned int r = csr_readl(0xe000680c);
	return r;
}
static inline void ulpi_phy1_ulpi_phy_tx_count_reset_write(unsigned int value) {
	csr_writel(value, 0xe000680c);
}
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_ADDR 0xe0006810
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_SIZE 1
static inline unsigned int ulpi_phy1_ulpi_phy_tx_count_read(void) {
	unsigned int r = csr_readl(0xe0006810);
	return r;
}

/* ulpi_sw_oe_n */
#define CSR_ULPI_SW_OE_N_BASE 0xe0009000
#define CSR_ULPI_SW_OE_N_OUT_ADDR 0xe0009000
#define CSR_ULPI_SW_OE_N_OUT_SIZE 1
static inline unsigned int ulpi_sw_oe_n_out_read(void) {
	unsigned int r = csr_readl(0xe0009000);
	return r;
}
static inline void ulpi_sw_oe_n_out_write(unsigned int value) {
	csr_writel(value, 0xe0009000);
}

/* ulpi_sw_s */
#define CSR_ULPI_SW_S_BASE 0xe0009800
#define CSR_ULPI_SW_S_OUT_ADDR 0xe0009800
#define CSR_ULPI_SW_S_OUT_SIZE 1
static inline unsigned int ulpi_sw_s_out_read(void) {
	unsigned int r = csr_readl(0xe0009800);
	return r;
}
static inline void ulpi_sw_s_out_write(unsigned int value) {
	csr_writel(value, 0xe0009800);
}

/* identifier_mem */
#define CSR_IDENTIFIER_MEM_BASE 0xe0002000

/* constants */
#define NMI_INTERRUPT 0
static inline int nmi_interrupt_read(void) {
	return 0;
}
#define TIMER0_INTERRUPT 1
static inline int timer0_interrupt_read(void) {
	return 1;
}
#define UART_INTERRUPT 2
static inline int uart_interrupt_read(void) {
	return 2;
}
#define CSR_DATA_WIDTH 32
static inline int csr_data_width_read(void) {
	return 32;
}
#define SYSTEM_CLOCK_FREQUENCY 100000000
static inline int system_clock_frequency_read(void) {
	return 100000000;
}
#define L2_SIZE 32
static inline int l2_size_read(void) {
	return 32;
}
#define CONFIG_CLOCK_FREQUENCY 100000000
static inline int config_clock_frequency_read(void) {
	return 100000000;
}
#define CONFIG_CPU_RESET_ADDR 0
static inline int config_cpu_reset_addr_read(void) {
	return 0;
}
#define CONFIG_CPU_TYPE "NONE"
static inline const char * config_cpu_type_read(void) {
	return "NONE";
}
#define CONFIG_CSR_DATA_WIDTH 32
static inline int config_csr_data_width_read(void) {
	return 32;
}

#endif
