# Lógica Fuzzy
Este projeto é uma aplicação integrada entre o Embarcadero RAD Studio e o Arduino, projetada para controlar e monitorar a velocidade de um cooler com base em dados de temperatura e distância, utilizando lógica fuzzy. 

O RAD Studio, com seu ambiente C++, desenvolve a interface gráfica, enquanto o Arduino gerencia a coleta de dados e o controle do cooler. A comunicação entre o software e o hardware é feita via porta serial, permitindo ajustes manuais através da interface do usuário e automaticamente com base nos parâmetros definidos pela lógica fuzzy. O projeto inclui funcionalidades como ajuste de velocidade do cooler em tempo real, visualização gráfica de dados, e a opção de operação manual ou automática com base nos inputs de sensores de temperatura e distância. 

![Screenshot_1](https://github.com/HenriqueDest/LogicaFuzzy/assets/104697173/0739aa78-f85e-464a-862d-04b289cb6c64)

## Para a instalação do projeto, é necessário:

Embarcadero RAD Studio: Instale a última versão do Embarcadero RAD Studio para desenvolvimento C++. Faça o download diretamente do site oficial.

Biblioteca TMS Async (VaComm): Necessária para comunicação serial no Embarcadero. Instale a biblioteca TMS Async seguindo as instruções no site oficial ou pelo GetIt Package Manager no RAD Studio.

Arduino IDE: Instale a IDE do Arduino para carregar o código no hardware. Disponível em arduino.cc.

### Hardware:

Arduino (Uno, Mega, etc.)
Sensor de temperatura (como LM35)
Sensor ultrassônico (HC-SR04)
Cooler ou motor DC
Transistor e diodo para controle do motor
Conexão Serial: Conecte o Arduino ao computador via cabo USB para a comunicação serial.

Configuração do Projeto: Carregue o código-fonte do Arduino utilizando a IDE do Arduino e abra o projeto no Embarcadero RAD Studio. Configure a porta COM correta nas propriedades do componente VaComm.

Siga as instruções detalhadas de cada ferramenta para a correta instalação e configuração, garantindo que todos os componentes estejam funcionando conforme esperado antes de prosseguir com o desenvolvimento ou uso do projeto.
