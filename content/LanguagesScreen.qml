import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 1920
    height: 1080

    CustomRadioButton {
        id: langFrenchButton
        x: 225
        y: 141
        backgroundImageSource: "images/c294_IdiomasfrancesRls.png"
        indicatorImageSource: "images/c295_IdiomasfrancesPress.png"
    }

    CustomRadioButton {
        id: langSpanishButton
        x: 371
        anchors.top: langFrenchButton.top
        backgroundImageSource: "images/c297_IdiomascastellanoRls.png"
        indicatorImageSource: "images/c298_IdiomascastellanoPress.png"
    }

    CustomRadioButton {
        id: langEnglishButton
        x: 515
        anchors.top: langFrenchButton.top
        backgroundImageSource: "images/c299_IdiomasinglesRls.png"
        indicatorImageSource: "images/c300_IdiomasinglesPress.png"
    }

    CustomRadioButton {
        id: langItalianButton
        x: 658
        anchors.top: langFrenchButton.top
        backgroundImageSource: "images/c301_IdiomasitalianoRls.png"
        indicatorImageSource: "images/c302_IdiomasitalianoPress.png"
    }

    CustomRadioButton {
        id: langGermanButton
        y: 294
        anchors.left: langFrenchButton.left
        backgroundImageSource: "images/c303_IdiomasalemanRls.png"
        indicatorImageSource: "images/c304_IdiomasalemanPress.png"
    }

    CustomRadioButton {
        id: langPolishButton
        anchors.left: langSpanishButton.left
        anchors.top: langGermanButton.top
        backgroundImageSource: "images/c305_IdiomaspolacoRls.png"
        indicatorImageSource: "images/c306_IdiomaspolacoPress.png"
    }

    CustomRadioButton {
        id: langRussianButton
        anchors.left: langEnglishButton.left
        anchors.top: langGermanButton.top
        backgroundImageSource: "images/c307_IdiomasrusoRls.png"
        indicatorImageSource: "images/c308_IdiomasrusoPress.png"
    }

    CustomRadioButton {
        id: langPortugueseButton
        anchors.left: langItalianButton.left
        anchors.top: langGermanButton.top
        backgroundImageSource: "images/c309_IdiomasportuguesRls.png"
        indicatorImageSource: "images/c310_IdiomasportuguesPress.png"
    }

    CustomRadioButton {
        id: langChineseButton
        y: 447
        anchors.left: langFrenchButton.left
        backgroundImageSource: "images/c311_IdiomaschinoRls.png"
        indicatorImageSource: "images/c312_IdiomaschinoPress.png"
    }

    CustomRadioButton {
        id: langJapaneseButton
        anchors.left: langSpanishButton.left
        anchors.top: langChineseButton.top
        backgroundImageSource: "images/c313_IdiomasjaponesRls.png"
        indicatorImageSource: "images/c314_IdiomasjaponesPress.png"
    }

    CustomRadioButton {
        id: langKoreanButton
        anchors.left: langEnglishButton.left
        anchors.top: langChineseButton.top
        backgroundImageSource: "images/c315_IdiomascoreanoRls.png"
        indicatorImageSource: "images/c316_IdiomascoreanoPress.png"
    }
//    CustomSwitch {
//        id: langFrenchButton
//        x: 225
//        y: 141
//        offStateImageSource: "images/c294_IdiomasfrancesRls.png"
//        onStateImageSource: "images/c295_IdiomasfrancesPress.png"
//    }

//    CustomSwitch {
//        id: langSpanishButton
//        x: 371
//        anchors.top: langFrenchButton.top
//        offStateImageSource: "images/c297_IdiomascastellanoRls.png"
//        onStateImageSource: "images/c298_IdiomascastellanoPress.png"
//    }

//    CustomSwitch {
//        id: langEnglishButton
//        x: 515
//        anchors.top: langFrenchButton.top
//        offStateImageSource: "images/c299_IdiomasinglesRls.png"
//        onStateImageSource: "images/c300_IdiomasinglesPress.png"
//    }

//    CustomSwitch {
//        id: langItalianButton
//        x: 658
//        anchors.top: langFrenchButton.top
//        offStateImageSource: "images/c301_IdiomasitalianoRls.png"
//        onStateImageSource: "images/c302_IdiomasitalianoPress.png"
//    }

//    CustomSwitch {
//        id: langGermanButton
//        y: 294
//        anchors.left: langFrenchButton.left
//        offStateImageSource: "images/c303_IdiomasalemanRls.png"
//        onStateImageSource: "images/c304_IdiomasalemanPress.png"
//    }

//    CustomSwitch {
//        id: langPolishButton
//        anchors.left: langSpanishButton.left
//        anchors.top: langGermanButton.top
//        offStateImageSource: "images/c305_IdiomaspolacoRls.png"
//        onStateImageSource: "images/c306_IdiomaspolacoPress.png"
//    }

//    CustomSwitch {
//        id: langRussianButton
//        anchors.left: langEnglishButton.left
//        anchors.top: langGermanButton.top
//        offStateImageSource: "images/c307_IdiomasrusoRls.png"
//        onStateImageSource: "images/c308_IdiomasrusoPress.png"
//    }

//    CustomSwitch {
//        id: langPortugueseButton
//        anchors.left: langItalianButton.left
//        anchors.top: langGermanButton.top
//        offStateImageSource: "images/c309_IdiomasportuguesRls.png"
//        onStateImageSource: "images/c310_IdiomasportuguesPress.png"
//    }

//    CustomSwitch {
//        id: langChineseButton
//        y: 447
//        anchors.left: langFrenchButton.left
//        offStateImageSource: "images/c311_IdiomaschinoRls.png"
//        onStateImageSource: "images/c312_IdiomaschinoPress.png"
//    }

//    CustomSwitch {
//        id: langJapaneseButton
//        anchors.left: langSpanishButton.left
//        anchors.top: langChineseButton.top
//        offStateImageSource: "images/c313_IdiomasjaponesRls.png"
//        onStateImageSource: "images/c314_IdiomasjaponesPress.png"
//    }

//    CustomSwitch {
//        id: langKoreanButton
//        anchors.left: langEnglishButton.left
//        anchors.top: langChineseButton.top
//        offStateImageSource: "images/c315_IdiomascoreanoRls.png"
//        onStateImageSource: "images/c316_IdiomascoreanoPress.png"
//    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}
}
##^##*/
