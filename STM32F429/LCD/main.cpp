/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE           1000

#define ILI9488_NOP           0x00
#define ILI9488_SWRESET       0x01
#define ILI9488_RDDID         0x04
#define ILI9488_RDDST         0x09

#define ILI9488_SLPIN         0x10
#define ILI9488_SLPOUT        0x11
#define ILI9488_PTLON         0x12
#define ILI9488_NORON         0x13

#define ILI9488_RDMODE        0x0A
#define ILI9488_RDMADCTL      0x0B
#define ILI9488_RDPIXFMT      0x0C
#define ILI9488_RDIMGFMT      0x0D
#define ILI9488_RDSELFDIAG    0x0F

#define ILI9488_INVOFF        0x20
#define ILI9488_INVON         0x21
#define ILI9488_GAMMASET      0x26
#define ILI9488_DISPOFF       0x28
#define ILI9488_DISPON        0x29

#define ILI9488_CASET         0x2A
#define ILI9488_PASET         0x2B
#define ILI9488_RAMWR         0x2C
#define ILI9488_RAMRD         0x2E

#define ILI9488_PTLAR         0x30
#define ILI9488_VSCRDEF       0x33
#define ILI9488_MADCTL        0x36
#define ILI9488_VSCRSADD      0x37
#define ILI9488_PIXFMT        0x3A
#define ILI9488_RAMWRCONT     0x3C
#define ILI9488_RAMRDCONT     0x3E

#define ILI9488_IMCTR         0xB0
#define ILI9488_FRMCTR1       0xB1
#define ILI9488_FRMCTR2       0xB2
#define ILI9488_FRMCTR3       0xB3
#define ILI9488_INVCTR        0xB4
#define ILI9488_DFUNCTR       0xB6

#define ILI9488_PWCTR1        0xC0
#define ILI9488_PWCTR2        0xC1
#define ILI9488_PWCTR3        0xC2
#define ILI9488_PWCTR4        0xC3
#define ILI9488_PWCTR5        0xC4
#define ILI9488_VMCTR1        0xC5
#define ILI9488_VMCTR2        0xC7

#define ILI9488_RDID1         0xDA
#define ILI9488_RDID2         0xDB
#define ILI9488_RDID3         0xDC
#define ILI9488_RDID4         0xDD

#define ILI9488_GMCTRP1       0xE0
#define ILI9488_GMCTRN1       0xE1
#define ILI9488_IMGFUNCT      0xE9

#define ILI9488_ADJCTR3       0xF7

#define ILI9488_MAD_RGB       0x08
#define ILI9488_MAD_BGR       0x00

#define ILI9488_MAD_VERTICAL  0x20
#define ILI9488_MAD_X_LEFT    0x00
#define ILI9488_MAD_X_RIGHT   0x40
#define ILI9488_MAD_Y_UP      0x80
#define ILI9488_MAD_Y_DOWN    0x00

#define ILI9488_MAD_COLORMODE    ILI9488_MAD_RGB

#define ILI9488_LCD_PIXEL_WIDTH 320
#define ILI9488_LCD_PIXEL_HEIGHT 480

/* the drawing directions of the 4 orientations */
#define ILI9488_MAX_X                      (ILI9488_LCD_PIXEL_WIDTH - 1)
#define ILI9488_MAX_Y                      (ILI9488_LCD_PIXEL_HEIGHT - 1)
#define ILI9488_MAD_DATA_RIGHT_THEN_UP     ILI9488_MAD_COLORMODE | ILI9488_MAD_X_RIGHT | ILI9488_MAD_Y_UP
#define ILI9488_MAD_DATA_RIGHT_THEN_DOWN   ILI9488_MAD_COLORMODE | ILI9488_MAD_X_RIGHT | ILI9488_MAD_Y_DOWN
#define ILI9488_SETCURSOR(x, y)            {LCD_IO_WriteCmd8(ILI9488_CASET); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_X - x); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_X - x); LCD_IO_WriteCmd8(ILI9488_PASET); LCD_IO_WriteData16_to_2x8(y); LCD_IO_WriteData16_to_2x8(y);}

#define ILI9488_LCD_INITIALIZED    0x01
#define ILI9488_IO_INITIALIZED     0x02

#define  ILI9488_LCDMUTEX_PUSH()
#define  ILI9488_LCDMUTEX_POP()

DigitalOut LCD_PWR_EN(MBED_CONF_APP_LCD_PWR_EN, 1);
DigitalOut LCD_BL(MBED_CONF_APP_LED_BACK_LIGHT, 0);
DigitalOut LCD_RST(MBED_CONF_APP_LCD_RST, 1);

SRAM_HandleTypeDef hsram1;
static uint32_t FMC_Initialized = 0;

void FMC_LCD_Gpio_Init(void)
{
    printf("%s\n", __func__);
    GPIO_InitTypeDef GPIO_InitStruct ={0};
    if (FMC_Initialized) {
        return;
    }
    printf("%s\n", __func__);
    FMC_Initialized = 1;

    /* Peripheral clock enable */
    __HAL_RCC_FMC_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_0|GPIO_PIN_4
        |GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14
        |GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_15|GPIO_PIN_12
        |GPIO_PIN_7|GPIO_PIN_14|GPIO_PIN_8|GPIO_PIN_13
        |GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void HAL_SRAM_MspDeInit(void)
{
    if (!FMC_Initialized) {
        return;
    }
    printf("%s\n", __func__);
    FMC_Initialized = 0;
    __HAL_RCC_FMC_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_0|GPIO_PIN_4 
            |GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14 
            |GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_15|GPIO_PIN_12 
            |GPIO_PIN_7|GPIO_PIN_14|GPIO_PIN_8|GPIO_PIN_13 
            |GPIO_PIN_9);
}

void FMC_LCD_Init(void)
{
    printf("%s\n", __func__);
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    FMC_NORSRAM_TimingTypeDef Timing = {0};

    hsram1.Instance = FMC_NORSRAM_DEVICE;
    hsram1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
    hsram1.Init.NSBank = FMC_NORSRAM_BANK1;
    hsram1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    hsram1.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
    hsram1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
    hsram1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
    hsram1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram1.Init.WrapMode = FMC_WRAP_MODE_DISABLE;
    hsram1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
    hsram1.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
    hsram1.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
    hsram1.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
    hsram1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
    hsram1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    hsram1.Init.PageSize = FMC_PAGE_SIZE_NONE;

    /* Timing */
    Timing.AddressSetupTime = 0;
    Timing.AddressHoldTime = 0;
    Timing.DataSetupTime = 3;
    Timing.BusTurnAroundDuration = 1;
    Timing.CLKDivision = 0;
    Timing.DataLatency = 0;
    Timing.AccessMode = FMC_ACCESS_MODE_A;

    /* ExtTiming */
    if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
    {
        while(1) {
            printf("error");
            ThisThread::sleep_for(500ms);
        }
    }
    FMC_LCD_Gpio_Init();
}

#define LCD_CMD      (*((volatile uint16_t *) 0x60000000))
#define LCD_DATA      (*((volatile uint16_t *) 0x60040000))

uint16_t lcd_data_get(void)
{
    return LCD_DATA;
}

void lcd_cmd(uint8_t cmd)
{
    LCD_CMD = cmd;
    // wait_ns(15);
}

void lcd_data_write(uint16_t data)
{
    LCD_DATA = data;
}

uint16_t lcd_data_read(void)
{
    return LCD_DATA;
}

void lcd_data_write_multiple8(uint8_t *data, size_t size)
{
    for(size_t i = 0; i < size; i++) {
        LCD_DATA = data[i];
    }
}

void lcd_data_write_fill(uint16_t data, size_t size)
{
    for(size_t i = 0; i < size; i++) {
        LCD_DATA = data;
    }
}

void lcd_data_write_16to8(uint16_t data)
{
    LCD_DATA = ((data >> 8) & 0xFF);
    LCD_DATA = ((data & 0xFF));
}

void lcd_cmd_multiple_data8(uint8_t cmd, uint8_t *data, size_t size)
{
    lcd_cmd(cmd);
    lcd_data_write_multiple8(data, size);
}

void ili9488_Init(void)
{
    lcd_cmd(ILI9488_SWRESET);
    ThisThread::sleep_for(5ms);
    // positive gamma control
    lcd_cmd_multiple_data8(ILI9488_GMCTRP1, (uint8_t *)"\x00\x03\x09\x08\x16\x0A\x3F\x78\x4C\x09\x0A\x08\x16\x1A\x0F", 15);
    // negative gamma control
    lcd_cmd_multiple_data8(ILI9488_GMCTRN1, (uint8_t *)"\x00\x16\x19\x03\x0F\x05\x32\x45\x46\x04\x0E\x0D\x35\x37\x0F", 15);
    // Power Control 1 (Vreg1out, Verg2out)
    lcd_cmd_multiple_data8(ILI9488_PWCTR1, (uint8_t *)"\x17\x15", 2);
    ThisThread::sleep_for(5ms);
    // Power Control 2 (VGH,VGL)
    lcd_cmd(ILI9488_PWCTR2); lcd_data_write(0x41);
    ThisThread::sleep_for(5ms);
    // Power Control 3 (Vcom)
    lcd_cmd_multiple_data8(ILI9488_VMCTR1, (uint8_t *)"\x00\x12\x80", 3);
    ThisThread::sleep_for(5ms);
    lcd_cmd(ILI9488_PIXFMT); lcd_data_write(0x55); // Interface Pixel Format (16 bit)
    lcd_cmd(ILI9488_FRMCTR1); lcd_data_write(0xA0); // Frame rate (60Hz)
    lcd_cmd(ILI9488_INVCTR); lcd_data_write(0x02); // Display Inversion Control (2-dot)
    lcd_cmd_multiple_data8(ILI9488_DFUNCTR, (uint8_t *)"\x02\x02", 2); // Display Function Control RGB/MCU Interface Control
    lcd_cmd(ILI9488_IMGFUNCT); lcd_data_write(0x00); // Set Image Functio (Disable 24 bit data)
    lcd_cmd_multiple_data8(ILI9488_ADJCTR3, (uint8_t *)"\xA9\x51\x2C\x82", 4); // Adjust Control (D7 stream, loose)
    ThisThread::sleep_for(5ms);
    lcd_cmd(ILI9488_SLPOUT);      // Exit Sleep
    ThisThread::sleep_for(120ms);
    lcd_cmd(ILI9488_DISPON);      // Display on
    ThisThread::sleep_for(5ms);
    lcd_cmd(ILI9488_MADCTL); lcd_data_write(ILI9488_MAD_DATA_RIGHT_THEN_DOWN);
}

void ili9488_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  ILI9488_LCDMUTEX_PUSH();

  lcd_cmd(ILI9488_CASET); lcd_data_write_16to8(ILI9488_LCD_PIXEL_WIDTH - Width - Xpos); lcd_data_write_16to8(ILI9488_LCD_PIXEL_WIDTH - 1 - Xpos);
  lcd_cmd(ILI9488_PASET); lcd_data_write_16to8(Ypos); lcd_data_write_16to8(Ypos + Height - 1);

  ILI9488_LCDMUTEX_POP();
}

void ili9488_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint16_t RGBCode)
{
  ILI9488_LCDMUTEX_PUSH();
  ili9488_SetDisplayWindow(Xpos, Ypos, Xsize, Ysize);
  lcd_cmd(ILI9488_RAMWR);
  lcd_data_write_fill(RGBCode, Xsize * Ysize);
  ILI9488_LCDMUTEX_POP();
}

int main()
{
    printf("Back light On\n");
    LCD_BL = 1;
    ThisThread::sleep_for(10s);

    FMC_LCD_Init();

    LCD_RST = 1;
    wait_us(100);
    LCD_RST = 0;
    wait_us(100);
    LCD_RST = 1;
    ThisThread::sleep_for(200ms);

    ili9488_Init();
    ili9488_FillRect(0, 0, ILI9488_LCD_PIXEL_WIDTH, ILI9488_LCD_PIXEL_HEIGHT, 0x001F);
    ThisThread::sleep_for(3s);

    ili9488_FillRect(0, 0, ILI9488_LCD_PIXEL_WIDTH, ILI9488_LCD_PIXEL_HEIGHT, 0xF100);
    ThisThread::sleep_for(3s);

    ili9488_FillRect(0, 0, ILI9488_LCD_PIXEL_WIDTH, ILI9488_LCD_PIXEL_HEIGHT, 0x07E0);
    uint16_t data[5];
    printf("Data Read\n");
    lcd_cmd(0x04);
    data[0] = lcd_data_read();
    data[1] = lcd_data_read();
    data[2] = lcd_data_read();
    data[3] = lcd_data_read();
    data[4] = lcd_data_read();

    for(int i = 0; i < 5; i++)
    {
        printf("LCD_DATA[%d] = %04X\n", i, data[i]);
    }

    while(1) {
        ThisThread::sleep_for(500ms);
    }
}
