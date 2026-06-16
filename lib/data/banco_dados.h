#ifndef BANCO_DADOS_H
#define BANCO_DADOS_H

#include <Arduino.h>


// Estrutura de dados para os locais
struct LocalSalvo {
    const char* nome;
    double latitude;
    double longitude;
};

const LocalSalvo BANCO_LOCAIS[] = {
    {"Casa", -22.9068, -43.1729},
    {"Trabalho", -23.5505, -46.6333},
    {"Ponto Pesca", -22.8123, -47.0645},
    {"Praia", -23.9618, -46.3322}
};
const uint8_t TOTAL_LOCAIS = sizeof(BANCO_LOCAIS) / sizeof(BANCO_LOCAIS[0]);


const char* const BANCO_TAGS[] = {
    "PESCA",
    "CASA",
    "PERIGO",
    "TRILHA",
    "VEICULO"
};
const uint8_t TOTAL_TAGS = sizeof(BANCO_TAGS) / sizeof(BANCO_TAGS[0]);

#endif