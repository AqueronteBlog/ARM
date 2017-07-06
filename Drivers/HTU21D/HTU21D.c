/**
 * @brief       HTU21D.h
 * @details     Digital Relative Humidity sensor with Temperature output.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "HTU21D.h"


 /**
 * @brief       uint8_t  HTU21D_Init    ( uint32_t SDA, uint32_t SCL, uint32_t MODE, uint32_t RESOLUTION, uint32_t HEATER )
 * @details     Initialing the HTU21D and defines
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
uint8_t  HTU21D_Init    ( uint32_t SDA, uint32_t SCL, uint32_t MODE, uint32_t RESOLUTION, uint32_t HEATER )
{
    uint8_t     cmd [] = { 0 };
    uint32_t    aux    =   0;


    HTU21D_SDA_pin   =   SDA;
    HTU21D_SCL_pin   =   SCL;
    HTU21D_Mode      =   MODE;

    // aux = i2c_read (  );

    cmd[0]           =   ( RESOLUTION | HEATER ) | USER_REGISTER_OTP_DISABLED;

   // aux = i2c_write (  );

   if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
   else
       return   HTU21D_FAILURE;

}



 /**
 * @brief       uint8_t  HTU21D_SoftReset   ( void )
 * @details     Rebooting the HTU21D sensor switching the power off and on again.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     The soft reset takes less than 15ms. The user must take this
 *              into account.
 */
uint8_t  HTU21D_SoftReset   ( void )
{
    uint8_t     cmd [] = { HTU21D_SOFT_RESET };
    uint32_t    aux    =   0;

    // i2c_write (  );

    if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
   else
       return   HTU21D_FAILURE;
}
