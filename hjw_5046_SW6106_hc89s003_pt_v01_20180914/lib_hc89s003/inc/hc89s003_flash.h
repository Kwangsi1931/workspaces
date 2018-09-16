/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.13
*   ************************************************************************************
**/

/**************************************************************************************/
#ifdef  _FLASH_
#define _FLASH_
#else
#define _FLASH_ extern
#endif
#include "HC89S003F4.h"
#include "app_cfg"
/**************************************************************************************/
/*IAP 命令寄存器 IAP_CMDH(默认值0),IAP_CMDL为IAP_CMDH的反码(默认值0xFF) */
#define FLASH_IAPCMD_UNLOCK         0xF00F  //解锁(22个CPU时钟后自动锁定,IAP_CMDH = 0)
#define FLASH_IAPCMD_ONEACTION      0xE11E  //触发一次操作
#define FLASH_IAPCMD_ERASESECTOR    0xD22D  //扇区擦除
#define FLASH_IAPCMD_BYTEPROGRAM    0xB44B  //字节编程
#define FLASH_IAPCMD_SOFTRESET      0x8778  //软件复位,复位地址为0000H,不重读代码选项
#define FLASH_IAPCMD_SOFTRESET_R    0x7887  //软件复位,复位地址为0000H,重读代码选项

/* IAP 地址寄存器 IAP_ADDRL,IAP_ADDRH (默认值为0xff) */
/* IAP 数据寄存器 IAP_DATA(默认值0) */
/**************************************************************************************/


/**************************************************************************************/
_FLASH_ void Flash_EraseBlock(u16 u16_addr);
_FLASH_ void Flash_WriteOneByteData(u16 u16_addr, u8 u8_data);
_FLASH_ void Flash_WriteAnyLengthData(u16 u16_addr, u8 u8_length, u8 *u8_save_arr);
_FLASH_ void Flash_ReadAnyLengthData(u16 u16_addr, u8 u8_length, u8 *u8_save_arr);
/**************************************************************************************/
