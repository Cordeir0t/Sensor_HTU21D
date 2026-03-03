
# Sensor_HTU21D

## Visão Geral

O projeto **Sensor_HTU21D** é uma implementação profissional para leitura de temperatura e umidade utilizando o sensor digital **HTU21D**, com comunicação via **I2C** e foco em aplicações embarcadas industriais, automação e sistemas IoT.

O projeto foi desenvolvido com foco em modularidade, confiabilidade, facilidade de manutenção e escalabilidade para integração com sistemas maiores.

---

## Arquitetura do Projeto

O sistema foi estruturado seguindo boas práticas de engenharia de software para sistemas embarcados:

* Camada de hardware
* Camada de abstração de sensor
* Camada de aplicação
* Interface de comunicação serial ou rede (quando aplicável)

---

## Características Técnicas

* Leitura de temperatura com alta precisão
* Leitura de umidade relativa
* Comunicação digital via barramento I2C
* Código otimizado para microcontroladores de baixo consumo
* Estrutura modular para expansão futura

---

## Especificações do Sensor

| Parâmetro               | Valor          |
| ----------------------- | -------------- |
| Protocolo               | I2C            |
| Alimentação             | 3.3V – 5V      |
| Faixa de temperatura    | -40°C a +125°C |
| Precisão de temperatura | ±0.3°C         |
| Faixa de umidade        | 0% a 100%      |
| Precisão de umidade     | ±2%            |

---

## Requisitos de Hardware

* Microcontrolador compatível com I2C (ESP32, ESP8266, Arduino, etc.)
* Sensor HTU21D
* Cabos de conexão apropriados
* Fonte de alimentação estável

### Pinagem

| HTU21D | Controlador |
| ------ | ----------- |
| VCC    | 3.3V ou 5V  |
| GND    | GND         |
| SDA    | GPIO SDA    |
| SCL    | GPIO SCL    |

---

## Requisitos de Software

* Arduino IDE ou PlatformIO
* Biblioteca Wire para comunicação I2C
* Compilador compatível com arquitetura do microcontrolador

---

## Instalação

### Clonar o repositório

```
git clone https://github.com/Cordeir0t/Sensor_HTU21D
```

### Compilar o projeto

Abra o projeto no ambiente de desenvolvimento e compile utilizando a ferramenta adequada.

---

## Uso

### Inicialização do Sensor

O sensor deve ser inicializado durante a inicialização do sistema.

### Leitura de Dados

Os dados podem ser lidos de forma periódica conforme necessidade da aplicação.

---

## Exemplo de Código

```cpp
#include <Wire.h>
#include "HTU21D.h"

HTU21D sensor;

void setup() {
    Serial.begin(115200);
    Wire.begin();

    sensor.begin();
}

void loop() {
    float temperatura = sensor.readTemperature();
    float umidade = sensor.readHumidity();

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    delay(2000);
}
```

---

## Tratamento de Erros

O sistema deve considerar:

* Falha na comunicação I2C
* Valores inválidos do sensor
* Timeout de leitura
* Inicialização incorreta do barramento

Recomenda-se implementar verificações de status antes do uso dos dados.

---

## Boas Práticas de Uso

* Utilizar alimentação estável
* Evitar interferências eletromagnéticas
* Manter cabos I2C o mais curtos possível
* Utilizar resistores de pull-up quando necessário

---

## Estrutura do Projeto

```
Sensor_HTU21D/
├── src/
├── include/
├── lib/
├── test/
├── platformio.ini
├── README.md
```

---

## Aplicações

* Automação industrial
* Sistemas de climatização
* Monitoramento ambiental
* Internet das Coisas (IoT)
* Controle de processos

---

## Segurança e Confiabilidade

* Validação de dados antes do uso
* Reconexão automática do barramento I2C
* Monitoramento de falhas de comunicação

---

## Licença

Projeto distribuído sob licença MIT.

---

## Contribuições

Pull requests são bem-vindos.
Para mudanças maiores, abra uma issue para discussão prévia.

---

