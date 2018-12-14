#ifndef __GENERATED_CSR_H
#define __GENERATED_CSR_H
#include <stdint.h>
#define CSR_ACCESSORS_DEFINED 1
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

/* ctrl */
#define CSR_CTRL_BASE 0xe0000000
#define CSR_CTRL_RESET_ADDR 0xe0000000
#define CSR_CTRL_RESET_SIZE 1
static inline unsigned char ctrl_reset_read(void) {
	unsigned char r = csr_readl(0xe0000000);
	return r;
}
static inline void ctrl_reset_write(unsigned char value) {
	csr_writel(value, 0xe0000000);
}
#define CSR_CTRL_SCRATCH_ADDR 0xe0000004
#define CSR_CTRL_SCRATCH_SIZE 4
static inline unsigned int ctrl_scratch_read(void) {
	unsigned int r = csr_readl(0xe0000004);
	r <<= 8;
	r |= csr_readl(0xe0000008);
	r <<= 8;
	r |= csr_readl(0xe000000c);
	r <<= 8;
	r |= csr_readl(0xe0000010);
	return r;
}
static inline void ctrl_scratch_write(unsigned int value) {
	csr_writel(value >> 24, 0xe0000004);
	csr_writel(value >> 16, 0xe0000008);
	csr_writel(value >> 8, 0xe000000c);
	csr_writel(value, 0xe0000010);
}
#define CSR_CTRL_BUS_ERRORS_ADDR 0xe0000014
#define CSR_CTRL_BUS_ERRORS_SIZE 4
static inline unsigned int ctrl_bus_errors_read(void) {
	unsigned int r = csr_readl(0xe0000014);
	r <<= 8;
	r |= csr_readl(0xe0000018);
	r <<= 8;
	r |= csr_readl(0xe000001c);
	r <<= 8;
	r |= csr_readl(0xe0000020);
	return r;
}

/* ddrphy */
#define CSR_DDRPHY_BASE 0xe0005000
#define CSR_DDRPHY_HALF_SYS8X_TAPS_ADDR 0xe0005000
#define CSR_DDRPHY_HALF_SYS8X_TAPS_SIZE 1
static inline unsigned char ddrphy_half_sys8x_taps_read(void) {
	unsigned char r = csr_readl(0xe0005000);
	return r;
}
static inline void ddrphy_half_sys8x_taps_write(unsigned char value) {
	csr_writel(value, 0xe0005000);
}
#define CSR_DDRPHY_DLY_SEL_ADDR 0xe0005004
#define CSR_DDRPHY_DLY_SEL_SIZE 1
static inline unsigned char ddrphy_dly_sel_read(void) {
	unsigned char r = csr_readl(0xe0005004);
	return r;
}
static inline void ddrphy_dly_sel_write(unsigned char value) {
	csr_writel(value, 0xe0005004);
}
#define CSR_DDRPHY_RDLY_DQ_RST_ADDR 0xe0005008
#define CSR_DDRPHY_RDLY_DQ_RST_SIZE 1
static inline unsigned char ddrphy_rdly_dq_rst_read(void) {
	unsigned char r = csr_readl(0xe0005008);
	return r;
}
static inline void ddrphy_rdly_dq_rst_write(unsigned char value) {
	csr_writel(value, 0xe0005008);
}
#define CSR_DDRPHY_RDLY_DQ_INC_ADDR 0xe000500c
#define CSR_DDRPHY_RDLY_DQ_INC_SIZE 1
static inline unsigned char ddrphy_rdly_dq_inc_read(void) {
	unsigned char r = csr_readl(0xe000500c);
	return r;
}
static inline void ddrphy_rdly_dq_inc_write(unsigned char value) {
	csr_writel(value, 0xe000500c);
}
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_RST_ADDR 0xe0005010
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_RST_SIZE 1
static inline unsigned char ddrphy_rdly_dq_bitslip_rst_read(void) {
	unsigned char r = csr_readl(0xe0005010);
	return r;
}
static inline void ddrphy_rdly_dq_bitslip_rst_write(unsigned char value) {
	csr_writel(value, 0xe0005010);
}
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_ADDR 0xe0005014
#define CSR_DDRPHY_RDLY_DQ_BITSLIP_SIZE 1
static inline unsigned char ddrphy_rdly_dq_bitslip_read(void) {
	unsigned char r = csr_readl(0xe0005014);
	return r;
}
static inline void ddrphy_rdly_dq_bitslip_write(unsigned char value) {
	csr_writel(value, 0xe0005014);
}

/* sdram */
#define CSR_SDRAM_BASE 0xe0004000
#define CSR_SDRAM_DFII_CONTROL_ADDR 0xe0004000
#define CSR_SDRAM_DFII_CONTROL_SIZE 1
static inline unsigned char sdram_dfii_control_read(void) {
	unsigned char r = csr_readl(0xe0004000);
	return r;
}
static inline void sdram_dfii_control_write(unsigned char value) {
	csr_writel(value, 0xe0004000);
}
#define CSR_SDRAM_DFII_PI0_COMMAND_ADDR 0xe0004004
#define CSR_SDRAM_DFII_PI0_COMMAND_SIZE 1
static inline unsigned char sdram_dfii_pi0_command_read(void) {
	unsigned char r = csr_readl(0xe0004004);
	return r;
}
static inline void sdram_dfii_pi0_command_write(unsigned char value) {
	csr_writel(value, 0xe0004004);
}
#define CSR_SDRAM_DFII_PI0_COMMAND_ISSUE_ADDR 0xe0004008
#define CSR_SDRAM_DFII_PI0_COMMAND_ISSUE_SIZE 1
static inline unsigned char sdram_dfii_pi0_command_issue_read(void) {
	unsigned char r = csr_readl(0xe0004008);
	return r;
}
static inline void sdram_dfii_pi0_command_issue_write(unsigned char value) {
	csr_writel(value, 0xe0004008);
}
#define CSR_SDRAM_DFII_PI0_ADDRESS_ADDR 0xe000400c
#define CSR_SDRAM_DFII_PI0_ADDRESS_SIZE 2
static inline unsigned short int sdram_dfii_pi0_address_read(void) {
	unsigned short int r = csr_readl(0xe000400c);
	r <<= 8;
	r |= csr_readl(0xe0004010);
	return r;
}
static inline void sdram_dfii_pi0_address_write(unsigned short int value) {
	csr_writel(value >> 8, 0xe000400c);
	csr_writel(value, 0xe0004010);
}
#define CSR_SDRAM_DFII_PI0_BADDRESS_ADDR 0xe0004014
#define CSR_SDRAM_DFII_PI0_BADDRESS_SIZE 1
static inline unsigned char sdram_dfii_pi0_baddress_read(void) {
	unsigned char r = csr_readl(0xe0004014);
	return r;
}
static inline void sdram_dfii_pi0_baddress_write(unsigned char value) {
	csr_writel(value, 0xe0004014);
}
#define CSR_SDRAM_DFII_PI0_WRDATA_ADDR 0xe0004018
#define CSR_SDRAM_DFII_PI0_WRDATA_SIZE 4
static inline unsigned int sdram_dfii_pi0_wrdata_read(void) {
	unsigned int r = csr_readl(0xe0004018);
	r <<= 8;
	r |= csr_readl(0xe000401c);
	r <<= 8;
	r |= csr_readl(0xe0004020);
	r <<= 8;
	r |= csr_readl(0xe0004024);
	return r;
}
static inline void sdram_dfii_pi0_wrdata_write(unsigned int value) {
	csr_writel(value >> 24, 0xe0004018);
	csr_writel(value >> 16, 0xe000401c);
	csr_writel(value >> 8, 0xe0004020);
	csr_writel(value, 0xe0004024);
}
#define CSR_SDRAM_DFII_PI0_RDDATA_ADDR 0xe0004028
#define CSR_SDRAM_DFII_PI0_RDDATA_SIZE 4
static inline unsigned int sdram_dfii_pi0_rddata_read(void) {
	unsigned int r = csr_readl(0xe0004028);
	r <<= 8;
	r |= csr_readl(0xe000402c);
	r <<= 8;
	r |= csr_readl(0xe0004030);
	r <<= 8;
	r |= csr_readl(0xe0004034);
	return r;
}
#define CSR_SDRAM_DFII_PI1_COMMAND_ADDR 0xe0004038
#define CSR_SDRAM_DFII_PI1_COMMAND_SIZE 1
static inline unsigned char sdram_dfii_pi1_command_read(void) {
	unsigned char r = csr_readl(0xe0004038);
	return r;
}
static inline void sdram_dfii_pi1_command_write(unsigned char value) {
	csr_writel(value, 0xe0004038);
}
#define CSR_SDRAM_DFII_PI1_COMMAND_ISSUE_ADDR 0xe000403c
#define CSR_SDRAM_DFII_PI1_COMMAND_ISSUE_SIZE 1
static inline unsigned char sdram_dfii_pi1_command_issue_read(void) {
	unsigned char r = csr_readl(0xe000403c);
	return r;
}
static inline void sdram_dfii_pi1_command_issue_write(unsigned char value) {
	csr_writel(value, 0xe000403c);
}
#define CSR_SDRAM_DFII_PI1_ADDRESS_ADDR 0xe0004040
#define CSR_SDRAM_DFII_PI1_ADDRESS_SIZE 2
static inline unsigned short int sdram_dfii_pi1_address_read(void) {
	unsigned short int r = csr_readl(0xe0004040);
	r <<= 8;
	r |= csr_readl(0xe0004044);
	return r;
}
static inline void sdram_dfii_pi1_address_write(unsigned short int value) {
	csr_writel(value >> 8, 0xe0004040);
	csr_writel(value, 0xe0004044);
}
#define CSR_SDRAM_DFII_PI1_BADDRESS_ADDR 0xe0004048
#define CSR_SDRAM_DFII_PI1_BADDRESS_SIZE 1
static inline unsigned char sdram_dfii_pi1_baddress_read(void) {
	unsigned char r = csr_readl(0xe0004048);
	return r;
}
static inline void sdram_dfii_pi1_baddress_write(unsigned char value) {
	csr_writel(value, 0xe0004048);
}
#define CSR_SDRAM_DFII_PI1_WRDATA_ADDR 0xe000404c
#define CSR_SDRAM_DFII_PI1_WRDATA_SIZE 4
static inline unsigned int sdram_dfii_pi1_wrdata_read(void) {
	unsigned int r = csr_readl(0xe000404c);
	r <<= 8;
	r |= csr_readl(0xe0004050);
	r <<= 8;
	r |= csr_readl(0xe0004054);
	r <<= 8;
	r |= csr_readl(0xe0004058);
	return r;
}
static inline void sdram_dfii_pi1_wrdata_write(unsigned int value) {
	csr_writel(value >> 24, 0xe000404c);
	csr_writel(value >> 16, 0xe0004050);
	csr_writel(value >> 8, 0xe0004054);
	csr_writel(value, 0xe0004058);
}
#define CSR_SDRAM_DFII_PI1_RDDATA_ADDR 0xe000405c
#define CSR_SDRAM_DFII_PI1_RDDATA_SIZE 4
static inline unsigned int sdram_dfii_pi1_rddata_read(void) {
	unsigned int r = csr_readl(0xe000405c);
	r <<= 8;
	r |= csr_readl(0xe0004060);
	r <<= 8;
	r |= csr_readl(0xe0004064);
	r <<= 8;
	r |= csr_readl(0xe0004068);
	return r;
}
#define CSR_SDRAM_DFII_PI2_COMMAND_ADDR 0xe000406c
#define CSR_SDRAM_DFII_PI2_COMMAND_SIZE 1
static inline unsigned char sdram_dfii_pi2_command_read(void) {
	unsigned char r = csr_readl(0xe000406c);
	return r;
}
static inline void sdram_dfii_pi2_command_write(unsigned char value) {
	csr_writel(value, 0xe000406c);
}
#define CSR_SDRAM_DFII_PI2_COMMAND_ISSUE_ADDR 0xe0004070
#define CSR_SDRAM_DFII_PI2_COMMAND_ISSUE_SIZE 1
static inline unsigned char sdram_dfii_pi2_command_issue_read(void) {
	unsigned char r = csr_readl(0xe0004070);
	return r;
}
static inline void sdram_dfii_pi2_command_issue_write(unsigned char value) {
	csr_writel(value, 0xe0004070);
}
#define CSR_SDRAM_DFII_PI2_ADDRESS_ADDR 0xe0004074
#define CSR_SDRAM_DFII_PI2_ADDRESS_SIZE 2
static inline unsigned short int sdram_dfii_pi2_address_read(void) {
	unsigned short int r = csr_readl(0xe0004074);
	r <<= 8;
	r |= csr_readl(0xe0004078);
	return r;
}
static inline void sdram_dfii_pi2_address_write(unsigned short int value) {
	csr_writel(value >> 8, 0xe0004074);
	csr_writel(value, 0xe0004078);
}
#define CSR_SDRAM_DFII_PI2_BADDRESS_ADDR 0xe000407c
#define CSR_SDRAM_DFII_PI2_BADDRESS_SIZE 1
static inline unsigned char sdram_dfii_pi2_baddress_read(void) {
	unsigned char r = csr_readl(0xe000407c);
	return r;
}
static inline void sdram_dfii_pi2_baddress_write(unsigned char value) {
	csr_writel(value, 0xe000407c);
}
#define CSR_SDRAM_DFII_PI2_WRDATA_ADDR 0xe0004080
#define CSR_SDRAM_DFII_PI2_WRDATA_SIZE 4
static inline unsigned int sdram_dfii_pi2_wrdata_read(void) {
	unsigned int r = csr_readl(0xe0004080);
	r <<= 8;
	r |= csr_readl(0xe0004084);
	r <<= 8;
	r |= csr_readl(0xe0004088);
	r <<= 8;
	r |= csr_readl(0xe000408c);
	return r;
}
static inline void sdram_dfii_pi2_wrdata_write(unsigned int value) {
	csr_writel(value >> 24, 0xe0004080);
	csr_writel(value >> 16, 0xe0004084);
	csr_writel(value >> 8, 0xe0004088);
	csr_writel(value, 0xe000408c);
}
#define CSR_SDRAM_DFII_PI2_RDDATA_ADDR 0xe0004090
#define CSR_SDRAM_DFII_PI2_RDDATA_SIZE 4
static inline unsigned int sdram_dfii_pi2_rddata_read(void) {
	unsigned int r = csr_readl(0xe0004090);
	r <<= 8;
	r |= csr_readl(0xe0004094);
	r <<= 8;
	r |= csr_readl(0xe0004098);
	r <<= 8;
	r |= csr_readl(0xe000409c);
	return r;
}
#define CSR_SDRAM_DFII_PI3_COMMAND_ADDR 0xe00040a0
#define CSR_SDRAM_DFII_PI3_COMMAND_SIZE 1
static inline unsigned char sdram_dfii_pi3_command_read(void) {
	unsigned char r = csr_readl(0xe00040a0);
	return r;
}
static inline void sdram_dfii_pi3_command_write(unsigned char value) {
	csr_writel(value, 0xe00040a0);
}
#define CSR_SDRAM_DFII_PI3_COMMAND_ISSUE_ADDR 0xe00040a4
#define CSR_SDRAM_DFII_PI3_COMMAND_ISSUE_SIZE 1
static inline unsigned char sdram_dfii_pi3_command_issue_read(void) {
	unsigned char r = csr_readl(0xe00040a4);
	return r;
}
static inline void sdram_dfii_pi3_command_issue_write(unsigned char value) {
	csr_writel(value, 0xe00040a4);
}
#define CSR_SDRAM_DFII_PI3_ADDRESS_ADDR 0xe00040a8
#define CSR_SDRAM_DFII_PI3_ADDRESS_SIZE 2
static inline unsigned short int sdram_dfii_pi3_address_read(void) {
	unsigned short int r = csr_readl(0xe00040a8);
	r <<= 8;
	r |= csr_readl(0xe00040ac);
	return r;
}
static inline void sdram_dfii_pi3_address_write(unsigned short int value) {
	csr_writel(value >> 8, 0xe00040a8);
	csr_writel(value, 0xe00040ac);
}
#define CSR_SDRAM_DFII_PI3_BADDRESS_ADDR 0xe00040b0
#define CSR_SDRAM_DFII_PI3_BADDRESS_SIZE 1
static inline unsigned char sdram_dfii_pi3_baddress_read(void) {
	unsigned char r = csr_readl(0xe00040b0);
	return r;
}
static inline void sdram_dfii_pi3_baddress_write(unsigned char value) {
	csr_writel(value, 0xe00040b0);
}
#define CSR_SDRAM_DFII_PI3_WRDATA_ADDR 0xe00040b4
#define CSR_SDRAM_DFII_PI3_WRDATA_SIZE 4
static inline unsigned int sdram_dfii_pi3_wrdata_read(void) {
	unsigned int r = csr_readl(0xe00040b4);
	r <<= 8;
	r |= csr_readl(0xe00040b8);
	r <<= 8;
	r |= csr_readl(0xe00040bc);
	r <<= 8;
	r |= csr_readl(0xe00040c0);
	return r;
}
static inline void sdram_dfii_pi3_wrdata_write(unsigned int value) {
	csr_writel(value >> 24, 0xe00040b4);
	csr_writel(value >> 16, 0xe00040b8);
	csr_writel(value >> 8, 0xe00040bc);
	csr_writel(value, 0xe00040c0);
}
#define CSR_SDRAM_DFII_PI3_RDDATA_ADDR 0xe00040c4
#define CSR_SDRAM_DFII_PI3_RDDATA_SIZE 4
static inline unsigned int sdram_dfii_pi3_rddata_read(void) {
	unsigned int r = csr_readl(0xe00040c4);
	r <<= 8;
	r |= csr_readl(0xe00040c8);
	r <<= 8;
	r |= csr_readl(0xe00040cc);
	r <<= 8;
	r |= csr_readl(0xe00040d0);
	return r;
}

/* ulpi_core0 */
#define CSR_ULPI_CORE0_BASE 0xe0006800
#define CSR_ULPI_CORE0_REG_ADR_ADDR 0xe0006800
#define CSR_ULPI_CORE0_REG_ADR_SIZE 1
static inline unsigned char ulpi_core0_reg_adr_read(void) {
	unsigned char r = csr_readl(0xe0006800);
	return r;
}
static inline void ulpi_core0_reg_adr_write(unsigned char value) {
	csr_writel(value, 0xe0006800);
}
#define CSR_ULPI_CORE0_REG_DAT_R_ADDR 0xe0006804
#define CSR_ULPI_CORE0_REG_DAT_R_SIZE 1
static inline unsigned char ulpi_core0_reg_dat_r_read(void) {
	unsigned char r = csr_readl(0xe0006804);
	return r;
}
#define CSR_ULPI_CORE0_REG_DAT_W_ADDR 0xe0006808
#define CSR_ULPI_CORE0_REG_DAT_W_SIZE 1
static inline unsigned char ulpi_core0_reg_dat_w_read(void) {
	unsigned char r = csr_readl(0xe0006808);
	return r;
}
static inline void ulpi_core0_reg_dat_w_write(unsigned char value) {
	csr_writel(value, 0xe0006808);
}
#define CSR_ULPI_CORE0_REG_WRITE_ADDR 0xe000680c
#define CSR_ULPI_CORE0_REG_WRITE_SIZE 1
static inline unsigned char ulpi_core0_reg_write_read(void) {
	unsigned char r = csr_readl(0xe000680c);
	return r;
}
static inline void ulpi_core0_reg_write_write(unsigned char value) {
	csr_writel(value, 0xe000680c);
}
#define CSR_ULPI_CORE0_REG_READ_ADDR 0xe0006810
#define CSR_ULPI_CORE0_REG_READ_SIZE 1
static inline unsigned char ulpi_core0_reg_read_read(void) {
	unsigned char r = csr_readl(0xe0006810);
	return r;
}
static inline void ulpi_core0_reg_read_write(unsigned char value) {
	csr_writel(value, 0xe0006810);
}
#define CSR_ULPI_CORE0_REG_DONE_ADDR 0xe0006814
#define CSR_ULPI_CORE0_REG_DONE_SIZE 1
static inline unsigned char ulpi_core0_reg_done_read(void) {
	unsigned char r = csr_readl(0xe0006814);
	return r;
}

/* ulpi_core1 */
#define CSR_ULPI_CORE1_BASE 0xe0007000
#define CSR_ULPI_CORE1_REG_ADR_ADDR 0xe0007000
#define CSR_ULPI_CORE1_REG_ADR_SIZE 1
static inline unsigned char ulpi_core1_reg_adr_read(void) {
	unsigned char r = csr_readl(0xe0007000);
	return r;
}
static inline void ulpi_core1_reg_adr_write(unsigned char value) {
	csr_writel(value, 0xe0007000);
}
#define CSR_ULPI_CORE1_REG_DAT_R_ADDR 0xe0007004
#define CSR_ULPI_CORE1_REG_DAT_R_SIZE 1
static inline unsigned char ulpi_core1_reg_dat_r_read(void) {
	unsigned char r = csr_readl(0xe0007004);
	return r;
}
#define CSR_ULPI_CORE1_REG_DAT_W_ADDR 0xe0007008
#define CSR_ULPI_CORE1_REG_DAT_W_SIZE 1
static inline unsigned char ulpi_core1_reg_dat_w_read(void) {
	unsigned char r = csr_readl(0xe0007008);
	return r;
}
static inline void ulpi_core1_reg_dat_w_write(unsigned char value) {
	csr_writel(value, 0xe0007008);
}
#define CSR_ULPI_CORE1_REG_WRITE_ADDR 0xe000700c
#define CSR_ULPI_CORE1_REG_WRITE_SIZE 1
static inline unsigned char ulpi_core1_reg_write_read(void) {
	unsigned char r = csr_readl(0xe000700c);
	return r;
}
static inline void ulpi_core1_reg_write_write(unsigned char value) {
	csr_writel(value, 0xe000700c);
}
#define CSR_ULPI_CORE1_REG_READ_ADDR 0xe0007010
#define CSR_ULPI_CORE1_REG_READ_SIZE 1
static inline unsigned char ulpi_core1_reg_read_read(void) {
	unsigned char r = csr_readl(0xe0007010);
	return r;
}
static inline void ulpi_core1_reg_read_write(unsigned char value) {
	csr_writel(value, 0xe0007010);
}
#define CSR_ULPI_CORE1_REG_DONE_ADDR 0xe0007014
#define CSR_ULPI_CORE1_REG_DONE_SIZE 1
static inline unsigned char ulpi_core1_reg_done_read(void) {
	unsigned char r = csr_readl(0xe0007014);
	return r;
}

/* ulpi_filter0 */
#define CSR_ULPI_FILTER0_BASE 0xe0007800
#define CSR_ULPI_FILTER0_MASK_ADDR 0xe0007800
#define CSR_ULPI_FILTER0_MASK_SIZE 2
static inline unsigned short int ulpi_filter0_mask_read(void) {
	unsigned short int r = csr_readl(0xe0007800);
	r <<= 8;
	r |= csr_readl(0xe0007804);
	return r;
}
static inline void ulpi_filter0_mask_write(unsigned short int value) {
	csr_writel(value >> 8, 0xe0007800);
	csr_writel(value, 0xe0007804);
}

/* ulpi_filter1 */
#define CSR_ULPI_FILTER1_BASE 0xe0008000
#define CSR_ULPI_FILTER1_MASK_ADDR 0xe0008000
#define CSR_ULPI_FILTER1_MASK_SIZE 2
static inline unsigned short int ulpi_filter1_mask_read(void) {
	unsigned short int r = csr_readl(0xe0008000);
	r <<= 8;
	r |= csr_readl(0xe0008004);
	return r;
}
static inline void ulpi_filter1_mask_write(unsigned short int value) {
	csr_writel(value >> 8, 0xe0008000);
	csr_writel(value, 0xe0008004);
}

/* ulpi_phy0 */
#define CSR_ULPI_PHY0_BASE 0xe0005800
#define CSR_ULPI_PHY0_ULPI_PHY_RESET_ADDR 0xe0005800
#define CSR_ULPI_PHY0_ULPI_PHY_RESET_SIZE 1
static inline unsigned char ulpi_phy0_ulpi_phy_reset_read(void) {
	unsigned char r = csr_readl(0xe0005800);
	return r;
}
static inline void ulpi_phy0_ulpi_phy_reset_write(unsigned char value) {
	csr_writel(value, 0xe0005800);
}
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_RESET_ADDR 0xe0005804
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_RESET_SIZE 1
static inline unsigned char ulpi_phy0_ulpi_phy_rx_count_reset_read(void) {
	unsigned char r = csr_readl(0xe0005804);
	return r;
}
static inline void ulpi_phy0_ulpi_phy_rx_count_reset_write(unsigned char value) {
	csr_writel(value, 0xe0005804);
}
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_ADDR 0xe0005808
#define CSR_ULPI_PHY0_ULPI_PHY_RX_COUNT_SIZE 4
static inline unsigned int ulpi_phy0_ulpi_phy_rx_count_read(void) {
	unsigned int r = csr_readl(0xe0005808);
	r <<= 8;
	r |= csr_readl(0xe000580c);
	r <<= 8;
	r |= csr_readl(0xe0005810);
	r <<= 8;
	r |= csr_readl(0xe0005814);
	return r;
}
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_RESET_ADDR 0xe0005818
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_RESET_SIZE 1
static inline unsigned char ulpi_phy0_ulpi_phy_tx_count_reset_read(void) {
	unsigned char r = csr_readl(0xe0005818);
	return r;
}
static inline void ulpi_phy0_ulpi_phy_tx_count_reset_write(unsigned char value) {
	csr_writel(value, 0xe0005818);
}
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_ADDR 0xe000581c
#define CSR_ULPI_PHY0_ULPI_PHY_TX_COUNT_SIZE 4
static inline unsigned int ulpi_phy0_ulpi_phy_tx_count_read(void) {
	unsigned int r = csr_readl(0xe000581c);
	r <<= 8;
	r |= csr_readl(0xe0005820);
	r <<= 8;
	r |= csr_readl(0xe0005824);
	r <<= 8;
	r |= csr_readl(0xe0005828);
	return r;
}

/* ulpi_phy1 */
#define CSR_ULPI_PHY1_BASE 0xe0006000
#define CSR_ULPI_PHY1_ULPI_PHY_RESET_ADDR 0xe0006000
#define CSR_ULPI_PHY1_ULPI_PHY_RESET_SIZE 1
static inline unsigned char ulpi_phy1_ulpi_phy_reset_read(void) {
	unsigned char r = csr_readl(0xe0006000);
	return r;
}
static inline void ulpi_phy1_ulpi_phy_reset_write(unsigned char value) {
	csr_writel(value, 0xe0006000);
}
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_RESET_ADDR 0xe0006004
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_RESET_SIZE 1
static inline unsigned char ulpi_phy1_ulpi_phy_rx_count_reset_read(void) {
	unsigned char r = csr_readl(0xe0006004);
	return r;
}
static inline void ulpi_phy1_ulpi_phy_rx_count_reset_write(unsigned char value) {
	csr_writel(value, 0xe0006004);
}
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_ADDR 0xe0006008
#define CSR_ULPI_PHY1_ULPI_PHY_RX_COUNT_SIZE 4
static inline unsigned int ulpi_phy1_ulpi_phy_rx_count_read(void) {
	unsigned int r = csr_readl(0xe0006008);
	r <<= 8;
	r |= csr_readl(0xe000600c);
	r <<= 8;
	r |= csr_readl(0xe0006010);
	r <<= 8;
	r |= csr_readl(0xe0006014);
	return r;
}
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_RESET_ADDR 0xe0006018
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_RESET_SIZE 1
static inline unsigned char ulpi_phy1_ulpi_phy_tx_count_reset_read(void) {
	unsigned char r = csr_readl(0xe0006018);
	return r;
}
static inline void ulpi_phy1_ulpi_phy_tx_count_reset_write(unsigned char value) {
	csr_writel(value, 0xe0006018);
}
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_ADDR 0xe000601c
#define CSR_ULPI_PHY1_ULPI_PHY_TX_COUNT_SIZE 4
static inline unsigned int ulpi_phy1_ulpi_phy_tx_count_read(void) {
	unsigned int r = csr_readl(0xe000601c);
	r <<= 8;
	r |= csr_readl(0xe0006020);
	r <<= 8;
	r |= csr_readl(0xe0006024);
	r <<= 8;
	r |= csr_readl(0xe0006028);
	return r;
}

/* ulpi_sw_oe_n */
#define CSR_ULPI_SW_OE_N_BASE 0xe0008800
#define CSR_ULPI_SW_OE_N_OUT_ADDR 0xe0008800
#define CSR_ULPI_SW_OE_N_OUT_SIZE 1
static inline unsigned char ulpi_sw_oe_n_out_read(void) {
	unsigned char r = csr_readl(0xe0008800);
	return r;
}
static inline void ulpi_sw_oe_n_out_write(unsigned char value) {
	csr_writel(value, 0xe0008800);
}

/* ulpi_sw_s */
#define CSR_ULPI_SW_S_BASE 0xe0009000
#define CSR_ULPI_SW_S_OUT_ADDR 0xe0009000
#define CSR_ULPI_SW_S_OUT_SIZE 1
static inline unsigned char ulpi_sw_s_out_read(void) {
	unsigned char r = csr_readl(0xe0009000);
	return r;
}
static inline void ulpi_sw_s_out_write(unsigned char value) {
	csr_writel(value, 0xe0009000);
}
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
#define CSR_DATA_WIDTH 8
static inline int csr_data_width_read(void) {
	return 8;
}
#define SYSTEM_CLOCK_FREQUENCY 100000000
static inline int system_clock_frequency_read(void) {
	return 100000000;
}
#define L2_SIZE 8192
static inline int l2_size_read(void) {
	return 8192;
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
#define CONFIG_CSR_DATA_WIDTH 8
static inline int config_csr_data_width_read(void) {
	return 8;
}

#endif
