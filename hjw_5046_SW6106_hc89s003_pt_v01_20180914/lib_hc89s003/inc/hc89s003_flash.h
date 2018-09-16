/**
*   ************************************************************************************
*                               ��о��������޹�˾
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
/*IAP ����Ĵ��� IAP_CMDH(Ĭ��ֵ0),IAP_CMDLΪIAP_CMDH�ķ���(Ĭ��ֵ0xFF) */
#define FLASH_IAPCMD_UNLOCK         0xF00F  //����(22��CPUʱ�Ӻ��Զ�����,IAP_CMDH = 0)
#define FLASH_IAPCMD_ONEACTION      0xE11E  //����һ�β���
#define FLASH_IAPCMD_ERASESECTOR    0xD22D  //��������
#define FLASH_IAPCMD_BYTEPROGRAM    0xB44B  //�ֽڱ��
#define FLASH_IAPCMD_SOFTRESET      0x8778  //�����λ,��λ��ַΪ0000H,���ض�����ѡ��
#define FLASH_IAPCMD_SOFTRESET_R    0x7887  //�����λ,��λ��ַΪ0000H,�ض�����ѡ��

/* IAP ��ַ�Ĵ��� IAP_ADDRL,IAP_ADDRH (Ĭ��ֵΪ0xff) */
/* IAP ���ݼĴ��� IAP_DATA(Ĭ��ֵ0) */
/**************************************************************************************/


/**************************************************************************************/
_FLASH_ void Flash_EraseBlock(u16 u16_addr);
_FLASH_ void Flash_WriteOneByteData(u16 u16_addr, u8 u8_data);
_FLASH_ void Flash_WriteAnyLengthData(u16 u16_addr, u8 u8_length, u8 *u8_save_arr);
_FLASH_ void Flash_ReadAnyLengthData(u16 u16_addr, u8 u8_length, u8 *u8_save_arr);
/**************************************************************************************/
