/*************************************************************************************
 * 文件:    config.c
 *
 * 描述:    slc设置
 *
 * 作者:    Jun
 *
 * 时间:    2011-2-20
*************************************************************************************/
#define  SLC_CONFIG_C
#include <includes.h>
#include "common.h"

/*------------------------------------------------------------------------------------
 * 
 *          文件名
 * 
**----------------------------------------------------------------------------------*/
static char *config_fname = "config.slc";   /* 配置文件名                    */
static char *unit_dat     = "unit.dat";     /* 初始设置文件名                */

#define config_magic   0x00434C53L          /* 配置文件标识字"SLC"           */

struct slc_config_s config = {
            config_magic,               /* 文件有效标识 */
            {                           /* 4个串口      */
                { 0x3F8, 38400L, 7, 1, COM_PARITY_EVEN, 4 },
                { 0x3E8, 38400L, 7, 1, COM_PARITY_EVEN, 3 },
                { 0x2F8,  9600L, 7, 1, COM_PARITY_EVEN, 5 },
                { 0x2E8, 38400L, 7, 1, COM_PARITY_EVEN, 7 },
            }, 
            /* 分压机默认参数由read_config()设置 */
};

/*------------------------------------------------------------------------------------
 * 函数:    read_config()
 *
 * 描述:    读取SLC配置文件
 *
 * 返回:    ok/fail
 *
 * 注意:    在读取成功后,激活了其中的设置
**----------------------------------------------------------------------------------*/
BOOL read_config(void)
{
    BOOL retval;
    int  fd = -1;

    retval = fail;
    
    lock_kernel();
    fd=open(config_fname, O_RDONLY|O_BINARY);
    if(fd<0){                                 /* 如果打开失败,则要尝试创建文件     */
        slc_setup_to_default(&config.slc[0]);
        slc_setup_to_default(&config.slc[1]);
        if(save_config()){
            fd=open(config_fname, O_RDONLY|O_BINARY);
        } else {
            retval=fail;                      /* 创建失败,可能是磁盘空间不足,退出! */
            goto out;
        }        
    }
    if(fd>=0){
        if(read(fd, (void *)&config, sizeof(config)) > 0){
            if(config.magic==config_magic){
                active_config();              /* 读取成功,激活其中的设置            */
                retval = ok;
            }
            
        }
        close(fd);
    }

out:
    unlock_kernel();
    return retval;
}

/*------------------------------------------------------------------------------------
 * 函数:    save_config()
 *
 * 描述:    保存(或创建)SLC配置文件
 *
 * 返回:    ok/fail
**----------------------------------------------------------------------------------*/
BOOL save_config(void)
{
    BOOL retval;
    int  fd = -1;

    retval = fail;
    
    lock_kernel();
    fd=open(config_fname, O_WRONLY|O_BINARY|O_CREAT, S_IREAD|S_IWRITE);
    if(fd>=0){
        check_config();
        if(write(fd, (void *)&config, sizeof(config)) > 0){
            retval=ok;
        }
        close(fd);
    }
    unlock_kernel();
    
    return retval;
}

/*------------------------------------------------------------------------------------
 * 函数:    active_config()
 *
 * 描述:    激活SLC设置
 *
 * 返回:    ok/fail
**----------------------------------------------------------------------------------*/
BOOL active_config(void)
{
    return ok;
}

/*------------------------------------------------------------------------------------
 * 函数:    check_config()
 *
 * 描述:    检测SLC配置并更正错误的设置
 *
 * 返回:    ok/fail
**----------------------------------------------------------------------------------*/
BOOL check_config(void)
{
    lock_kernel();
    if(config.magic!=config_magic){
        config.magic=config_magic;
    }
    unlock_kernel();
    return ok;
}

/*------------------------------------------------------------------------------------
 * 函数:    read_init_setup()
 *
 * 描述:    读取SLC初始设置
 *
 * 返回:    ok/fail
 *
 * 说明:    SLC初始设置与SLC配置有所不同, SLC初始设置只能在程序外边修改, 在程序中
 *          也只会读取一次, 而SLC的配置是在程序内部修改的, 并可修改多次
 *
 *          SLC初始设置文件: unit.dat   //不能自动生成
 *          SLC配置文件:     config.slc //可以自动生成, 但所有参数都被复位到了默认值
**----------------------------------------------------------------------------------*/
void read_init_setup(void)
{    
    int  fd = -1;
    
    lock_kernel();
    fd=open(unit_dat, O_RDONLY|O_BINARY);
    if(fd>=0){
        /* 处理过程 */
        close(fd);
    }
    unlock_kernel();
}

/*------------------------------------------------------------------------------------
 * 函数:    config_init_gui()
 *
 * 描述:    SLC参数修改界面初始化
 *
 * 返回:    ok/fail
**----------------------------------------------------------------------------------*/
void config_init_gui(void)
{


}

/*------------------------------------------------------------------------------------
 * 函数:    modify_config()
 *
 * 描述:    修改SLC参数
 *
 * 返回:    ok/fail
 *
 * 说明:    SLC修改参数的用户接口
**----------------------------------------------------------------------------------*/
BOOL modify_config(int slc_no)
{


}



/*====================================================================================
 * 
 * 本文件结束: config.c
 * 
**==================================================================================*/

