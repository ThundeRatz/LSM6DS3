# LSM6DS3

Biblioteca adaptada do [driver da ST](https://github.com/STMicroelectronics/STMems_Standard_C_drivers/tree/master/lsm6ds3_STdC) para utilizar o sensor de 6 eixos LSM6DS3 (Os arquivos `lsm6ds3_reg.h/.c` não foram modificados)

# Utilização
## Cube:
* I2C:
    * É possível usar em normal mode (100 kHz) ou em fast mode (400 kHz)
* SPI:
    * A frequência máxima de clock é 10 MHz
    * CPOL deve ter valor 1 (High) e CPHA deve ter valor 1 (2 Edge)
    * É necessário escolher um pino e setar como GPIO_Output, esse pino será usado como Chip Select

## No arquivo lsm6ds3.c:
* Descomentar a linha com o protocolo usado e comentar a outra
  * Para I2C:
    ```c
    // #define SPI
    #define I2C
    ```
  * Para SPI:
    ```c
    #define SPI
    // #define I2C
    ```

* Para usar interrupt
    * Descomentar a linha
      ```c
      #define USE_INTERRUPT
      ```
    * Modificar as linhas seguintes de acordo com o projeto:
      ```c
      #define INT_GPIO_PORT_XL GPIOC
      #define INT_PIN_XL GPIO_PIN_1
      #define INT_GPIO_PORT_G GPIOC
      #define INT_PIN_G GPIO_PIN_2
      #define INT1_DRDY_XL PROPERTY_ENABLE
      #define INT1_DRDY_G PROPERTY_DISABLE
      #define INT2_DRDY_XL PROPERTY_DISABLE
      #define INT2_DRDY_G PROPERTY_ENABLE
      ```

* Para I2C: modificar `SENSOR_BUS` e `I2C_INIT`
    ```c
    // I2C2
    #define SENSOR_BUS hi2c2
    #define I2C_INIT MX_I2C2_Init
    ```

* Para SPI: modificar `SENSOR_BUS`, `SPI_INIT`, `CS_GPIO_PORT` e `CS_PIN`
    ```c
    // SPI1 com PA4 como Chip Select
    #define SENSOR_BUS hspi1
    #define SPI_INIT MX_SPI1_Init
    #define CS_GPIO_PORT GPIOA
    #define CS_PIN GPIO_PIN_4
    ```

## Inicialização:
* Criar uma struct que contém os valores desejados de sensibilidades e de frequências de amostragem do acelerômetro e do giroscópio
  ```c
  // Exemplo
  lsm6ds3_settings_t lsm6ds3_settings = {
      .lsm6ds3_xl_fs = LSM6DS3_16g,
      .lsm6ds3_fs_g = LSM6DS3_2000dps,
      .lsm6ds3_odr_xl = LSM6DS3_XL_ODR_6k66Hz,
      .lsm6ds3_odr_g = LSM6DS3_GY_ODR_1k66Hz
  };
  ```
* Para inicializar o sensor, use a função
  ```c
  int8_t lsm6ds3_init(lsm6ds3_settings_t lsm6ds3_settings)
  ```
* A função `lsm6ds3_init` retorna `1` caso haja erro na leitura do registrador `WHO_AM_I` do sensor

## Para obter as leituras do sensor:
* Primeiro é necessário atualizar os dados brutos:
  * Se os pinos INT não estão sendo usados, use a função:
    ```c
    void lsm6ds3_update_data()
    ```
  * Se os pinos INT estão sendo usados, use a função:
    ```c
    void lsm6ds3_update_data_interrupt()
    ```
* Depois disso, para obter as leituras já convertidas, use as funções 
  ```c
  float* lsm6ds3_get_acc_data_mg()
  float* lsm6ds3_get_gyro_data_mdps()
  ```

---------------------

Equipe ThundeRatz de Robótica