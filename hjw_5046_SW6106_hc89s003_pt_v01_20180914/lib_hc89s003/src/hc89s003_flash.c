/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.13
*   ************************************************************************************
**/

/***************************************************************************************
*                           模块性能介绍
*   1、Flash擦写次数10万次以上
*   2、扇区擦除时间约5ms，且擦除时不响应任何中断，但会置相关标志位，擦除完成后响应
*   3、可设置应用程序读保护，应用程序写保护（以4K字节为保护单位）
*   4、可以设置仿真器扇区读保护，扇区写保护（以4K字节为保护单位）
*   5、设置保护后无法擦写程序，读取的数据全为零
*   6、每一颗MCU在出厂时会固化一个CHIP_ID，一共8个字节，一颗芯片一个ID，不会重复
*   ************************************************************************************
*                                    应用注意事项
*   1、CPU时钟需要配置为1-16MHz之间的正整数，且Flash擦写之前需要配置FREQ_CLK寄存器，该寄
*      存器值即为当前CPU时钟频率。
*   2、扇区擦除写入过程中不能被打断
*   3、数据存放地址需要在程序存放地址之后
*   4、第二复位向量使能时，无法在仿真环境下查看code区数据
*   5、Flsah操作最低电压限制为2.0V，所以建议进行Flash操作前进行电压检测或者打开BOR，BOR电
*      压建议设置为2.4V及2.4V以上
*   6、建议在进行Flash擦写操作前关闭中断，擦写完成后再打开中断
/**************************************************************************************/
#define _FLASH_
#include "flash.h"
#include "register.h"

/***************************************************************************************
* #pragma disable 含义:在函数前声明,只对一个函数有效,该函数调用过程中将不可被中断
* GF90F0320一共128个扇区;128个字节为一个扇区;8*128 = 1K 为一页;1K*4 = 4K 为一块
/**************************************************************************************/



/***************************************************************************************
* @功能    扇区擦除,约5ms的时间
* @说明
* @参数    擦除扇区内的任意地址
* @返回值  无
* @注      只要操作扇区里面的任意一个地址就可以擦除此扇区
***************************************************************************************/
#pragma disable
void Flash_EraseBlock(u16 u16_addr)
{
    //Flash解锁
    IAP_CMD = FLASH_IAPCMD_UNLOCK;
    //写入擦除地址
    IAP_ADDR = u16_addr;
    //选择操作方式:扇区擦除
    IAP_CMD = FLASH_IAPCMD_ERASESECTOR;
    //触发后IAP_ADDRL&IAP_ADDRH指向0xFF,同时自动锁定
    //触发一次操作
    IAP_CMD = FLASH_IAPCMD_ONEACTION;
}
/**************************************************************************************/


/***************************************************************************************
* @说明     写入一个字节数据到Flash里面
* @参数     u16_addr : FLASH地址
* @参数     u8_data  ：写入的数据
* @返回值 无
* @注       写之前必须先对操作的扇区进行擦除
***************************************************************************************/
#pragma disable
void Flash_WriteOneByteData(u16 u16_addr, u8 u8_data)
{
    //写入数据
    IAP_DATA = u8_data;
    //Flash解锁
    IAP_CMD = FLASH_IAPCMD_UNLOCK;
    //写入FLASH地址
    IAP_ADDR = u16_addr;
    //字节编程
    IAP_CMD = FLASH_IAPCMD_BYTEPROGRAM;
    //
    //触发一次操作
    IAP_CMD = FLASH_IAPCMD_ONEACTION;
}
/**************************************************************************************/


/***************************************************************************************
* @功能     写入任意长度的数据到flash里面
* @说明
* @参数     u16_addr ：FLASH起始地址
* @参数     u8_length: 写入数据长度(取值范围：0x00-0xFF)
* @参数     *u8_save_arr：写入的数据存放区域的首地址(RAM数组的首地址)
* @返回值   无
* @注       写之前必须先对操作的扇区进行擦除
***************************************************************************************/
#pragma disable
void Flash_WriteAnyLengthData(u16 u16_addr, u8 u8_length, u8 *u8_save_arr)
{
    u8 i;

    for(i = 0; i < u8_length; i++)
    {
        Flash_WriteOneByteData(u16_addr, *u8_save_arr);
        u16_addr++;
        u8_save_arr++;
    }
}
/**************************************************************************************/


/***************************************************************************************
* @功能     从flash里面读取任意长度的数据
* @说明
* @参数     u16_addr ：flash读取数据起始地址
* @参数     u8_length ：读取数据长度(取值范围：0x00-0xFF)
* @参数     *u8_save_arr：读取数据存放的区域首地址
* @返回值   无
* @注       无
***************************************************************************************/
void Flash_ReadAnyLengthData(u16 u16_addr, u8 u8_length, u8 *u8_save_arr)
{
    do
    {
        //读取数据
        *u8_save_arr = *((u8 code *)(u16_addr));
        u8_save_arr++;
        u16_addr++;
        u8_length--;
    }
    while(u8_length);
}
/**************************************************************************************/
