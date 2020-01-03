# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/Users/sol/dev/lib/USD/pxr/usdImaging/lib/usdviewq/adjustClippingUI.ui'
#
# Created: Wed Dec  4 17:02:40 2019
#      by: pyside-uic 0.2.15 running on PySide 1.2.4
#
# WARNING! All changes made in this file will be lost!

from Qt import QtWidgets
from Qt import QtCore


class Ui_AdjustClipping(object):
    def setupUi(self, AdjustClipping):
        AdjustClipping.setObjectName("AdjustClipping")
        AdjustClipping.resize(331, 81)
        self.verticalLayout = QtWidgets.QVBoxLayout(AdjustClipping)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.overrideNear = QtWidgets.QCheckBox(AdjustClipping)
        self.overrideNear.setFocusPolicy(QtCore.Qt.NoFocus)
        self.overrideNear.setObjectName("overrideNear")
        self.verticalLayout_2.addWidget(self.overrideNear)
        self.overrideFar = QtWidgets.QCheckBox(AdjustClipping)
        self.overrideFar.setFocusPolicy(QtCore.Qt.NoFocus)
        self.overrideFar.setObjectName("overrideFar")
        self.verticalLayout_2.addWidget(self.overrideFar)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.nearEdit = QtWidgets.QLineEdit(AdjustClipping)
        self.nearEdit.setObjectName("nearEdit")
        self.verticalLayout_3.addWidget(self.nearEdit)
        self.farEdit = QtWidgets.QLineEdit(AdjustClipping)
        self.farEdit.setObjectName("farEdit")
        self.verticalLayout_3.addWidget(self.farEdit)
        self.horizontalLayout.addLayout(self.verticalLayout_3)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.retranslateUi(AdjustClipping)
        QtCore.QMetaObject.connectSlotsByName(AdjustClipping)

    def retranslateUi(self, AdjustClipping):
        AdjustClipping.setProperty("comment", QtWidgets.QApplication.translate("AdjustClipping", "\n"
"     Copyright 2016 Pixar                                                                   \n"
"                                                                                            \n"
"     Licensed under the Apache License, Version 2.0 (the \"Apache License\")      \n"
"     with the following modification; you may not use this file except in                   \n"
"     compliance with the Apache License and the following modification to it:               \n"
"     Section 6. Trademarks. is deleted and replaced with:                                   \n"
"                                                                                            \n"
"     6. Trademarks. This License does not grant permission to use the trade                 \n"
"        names, trademarks, service marks, or product names of the Licensor                  \n"
"        and its affiliates, except as required to comply with Section 4(c) of               \n"
"        the License and to reproduce the content of the NOTICE file.                        \n"
"                                                                                            \n"
"     You may obtain a copy of the Apache License at                                         \n"
"                                                                                            \n"
"         http://www.apache.org/licenses/LICENSE-2.0                                         \n"
"                                                                                            \n"
"     Unless required by applicable law or agreed to in writing, software                    \n"
"     distributed under the Apache License with the above modification is                    \n"
"     distributed on an \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY   \n"
"     KIND, either express or implied. See the Apache License for the specific               \n"
"     language governing permissions and limitations under the Apache License.               \n"
"  ", None))
        AdjustClipping.setWindowTitle(QtWidgets.QApplication.translate("AdjustClipping", "Adjust Clipping Planes", None))
        self.overrideNear.setText(QtWidgets.QApplication.translate("AdjustClipping", "Override Near", None))
        self.overrideFar.setText(QtWidgets.QApplication.translate("AdjustClipping", "Override Far", None))

