/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PA_0, /* SYS_WKUP0 */
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = PA_2, /* SYS_WKUP1 */
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = PC_13, /* SYS_WKUP2 */
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PI_8, /* SYS_WKUP3 - Manually added */
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5 = PI_11, /* SYS_WKUP4 - Manually added */
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6 = PC_1, /* SYS_WKUP5 */
#endif
#ifdef PWR_WAKEUP_PIN7
  SYS_WKUP7 = NC,
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8 = NC,
#endif
/* USB */
#ifdef USBCON
  USB_OTG_FS_SOF = PA_8,
  USB_OTG_FS_VBUS = PA_9,
  USB_OTG_FS_ID = PA_10,
  USB_OTG_FS_DM = PA_11,
  USB_OTG_FS_DP = PA_12,
  USB_OTG_HS_ULPI_D0 = PA_3,
  USB_OTG_HS_SOF = PA_4,
  USB_OTG_HS_ULPI_CK = PA_5,
  USB_OTG_HS_ULPI_D1 = PB_0,
  USB_OTG_HS_ULPI_D2 = PB_1,
  USB_OTG_HS_ULPI_D7 = PB_5,
  USB_OTG_HS_ULPI_D3 = PB_10,
  USB_OTG_HS_ULPI_D4 = PB_11,
  USB_OTG_HS_ID = PB_12,
  USB_OTG_HS_ULPI_D5 = PB_12,
  USB_OTG_HS_ULPI_D6 = PB_13,
  USB_OTG_HS_VBUS = PB_13,
  USB_OTG_HS_DM = PB_14,
  USB_OTG_HS_DP = PB_15,
  USB_OTG_HS_ULPI_STP = PC_0,
  USB_OTG_HS_ULPI_DIR = PC_2,
  USB_OTG_HS_ULPI_NXT = PC_3,
#endif

  // Digtial pins alias
  EINK_BUSY 	= PC_15, // D0
  EINK_CMD		= PC_14, // D1
  EPD_CKV		= PJ_8, // D2
  EPD_CL		= PJ_9, // D3
  EPD_D0		= PD_2, // D4
  EPD_D1		= PD_3, // D5
  EPD_D2		= PD_4, // D6
  EPD_D3		= PD_5, // D7
  EPD_D4		= PD_6, // D8
  EPD_D5		= PD_7, // D9
  EPD_D6		= PD_11, // D10
  EPD_D7		= PD_12, // D11
  EPD_GMODE		= PJ_10, // D12
  EPD_LE		= PJ_11, // D13
  EPD_OE		= PK_0, // D14
  EPD_SPH		= PK_1, // D15
  EPD_SPV		= PK_2, // D16

  IMU_DRDY		= PB_0, // D17
  IMU_FSYNC		= PB_1, // D18
  IMU_nINT		= PB_2, // D19
  KEY_DOWN		= PC_7, // D20
  KEY_ENTER		= PA_0, // D21
  KEY_ESCAPE	= PC_13, // D22
  KEY_FUNC1		= PC_8, // D23
  KEY_FUNC2		= PC_9, // D24
  KEY_LEFT		= PC_4, // D25
  KEY_MENU		= PA_1, // D26
  KEY_RIGHT		= PC_5, // D27
  KEY_UP		= PC_6, // D28
  RPI_STATUS	= PC_1, // D29
  PMIC_PWRUP	= PG_11, // D30
  PMIC_VCOM		= PG_9, // D31
  PMIC_WAKEUP	= PG_10, // D32
  PWR_5V_EN		= PB_9, // D33
  PWR_EN_BATp	= PG_3, // D34
  PWR_EN_EXTRA	= PG_3, // D34
  PWR_EN_PMIC	= PG_3, // D34
  PWR_EN_PERIPH	= PG_7, // D35
  PWR_LED1		= PG_14, // D36
  PWR_LED2		= PG_13, // D37

  USB_OTG_FS_VBUS	= PC_12, // D38
  USB_OTG_HS_ID		= PB_12, // D39
  USB_OTG_HS_OVCR	= PA_8, // D40
  USB_OTG_HS_PWR_EN	= PD_13, // D41
  USB_OTG_HS_VBUS	= PB_13, // D42
