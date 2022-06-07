import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    Image {
        id: backgroundImg
        anchors.centerIn: parent
        source: "images/b001_FondoLogoSiluetasHombreMujer.png"
    }

    TwoStateButton {
        id: genderSelectButtonFemale
        y: 276
        anchors.left: parent.left
        imageSourcePressed: "images/b002_BotonFemeninoPress.png"
        imageSourceReleased: "images/b003_BotonFemeninoRls.png"
        button.onReleased: cbkWpr.butGenderSelect(AppEnumsNs.AppGUIbodyFemale)
    }

    TwoStateButton {
        id: genderSelectButtonMale
        y: genderSelectButtonFemale.y
        anchors.right: parent.right
        imageSourcePressed: "images/b005_BotonMasculinoPress.png"
        imageSourceReleased: "images/b006_BotonMasculinoRls.png"
        button.onReleased: cbkWpr.butGenderSelect(AppEnumsNs.AppGUIbodyMale)
    }
}





