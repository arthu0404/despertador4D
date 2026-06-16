#include "gps_screen.h"
#include "home_screen.h"
#include "../screen_manager.h"  
#include "../../gps/gps.h"
#include "../../data/banco_dados.h"

extern GpsManager myGps;
extern HomeScreen homeScreen; 

GPSScreen::GPSScreen() {
    _subTab = 0;
    _isSelecting = false;
    _localIndex = 0;
    _isSelectingTag = false;
    _tagIndex = 0;
}

void GPSScreen::onEnter() {
    _subTab = 0; 
    _isSelecting = false;
    _isSelectingTag = false;
}

void GPSScreen::draw(Display* display) {
    String nomeExibicao = myGps.hasDestination() ? myGps.getDestName() : "Nenhum";
    String distExibicao = myGps.getDistanceString();
    String tagExibicao = String(BANCO_TAGS[_tagIndex]);

    //  Aba 0 - Locais
    if (_subTab == 0 && _isSelecting) {
        nomeExibicao = "> " + String(BANCO_LOCAIS[_localIndex].nome);
        distExibicao = "Selecionando...";
    }

    // Aba 2 - Tags
    if (_subTab == 2 && _isSelectingTag) {
        tagExibicao = ">" + tagExibicao + "<"; 
    }

    display->showGPSScreen(
        _subTab,
        myGps.isConnected(),
        myGps.getDetailedStatus(),
        myGps.getSearchTime(),
        myGps.getSatellites(),
        myGps.getLat(),
        myGps.getLng(),
        myGps.getAltitude(),
        myGps.getSpeed(),
        myGps.hasDestination(), 
        nomeExibicao,
        distExibicao,
        tagExibicao
    );
}

void GPSScreen::handleInput(EncoderAction action, ScreenManager* manager) {
    // Selecionando um Destino (Aba Locais)
    if (_subTab == 0 && _isSelecting) {
        if (action == ENC_NEXT) {
            _localIndex = (_localIndex + 1) % TOTAL_LOCAIS;
        } 
        else if (action == ENC_PREV) {
            _localIndex = (_localIndex == 0) ? TOTAL_LOCAIS - 1 : _localIndex - 1;
        } 
        else if (action == ENC_CLICK) {
            myGps.setDestination(BANCO_LOCAIS[_localIndex].latitude, BANCO_LOCAIS[_localIndex].longitude, BANCO_LOCAIS[_localIndex].nome);
            _isSelecting = false; 
            Serial.println("Destino definido com sucesso!");
        }
        return; 
    }

    // Escolhendo uma Tag (Aba Marcar)
    if (_subTab == 2 && _isSelectingTag) {
        if (action == ENC_NEXT) {
            _tagIndex = (_tagIndex + 1) % TOTAL_TAGS;
        } 
        else if (action == ENC_PREV) {
            _tagIndex = (_tagIndex == 0) ? TOTAL_TAGS - 1 : _tagIndex - 1;
        } 
        else if (action == ENC_CLICK) {
            _isSelectingTag = false; 
            Serial.printf("Ponto de GPS (%f, %f) salvo com a Tag: %s\n", myGps.getLat(), myGps.getLng(), BANCO_TAGS[_tagIndex]);
        }
        return; 
    }

    // NAVEGAÇÃO COMUM: Mudando as abas laterais
    if (action == ENC_NEXT) {
        _subTab = (_subTab + 1) % 3; 
    } 
    else if (action == ENC_PREV) {
        _subTab = (_subTab == 0) ? 2 : _subTab - 1; 
    } 
    else if (action == ENC_CLICK) {
        if (_subTab == 0) {
            _isSelecting = true; // Entra na lista de Locais
        }
        else if (_subTab == 2) {
            _isSelectingTag = true; // Entra na lista de Tags
        }
    }
    else if (action == ENC_LONG_CLICK) {
        manager->changeScreen(&homeScreen);
    }
}