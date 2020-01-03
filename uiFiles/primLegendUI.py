# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/Users/sol/dev/lib/USD/pxr/usdImaging/lib/usdviewq/primLegendUI.ui'
#
# Created: Wed Dec  4 17:02:40 2019
#      by: pyside-uic 0.2.15 running on PySide 1.2.4
#
# WARNING! All changes made in this file will be lost!

from Qt import QtWidgets
from Qt import QtCore
from Qt import QtGui

class Ui_PrimLegend(object):
    def setupUi(self, PrimLegend):
        PrimLegend.setObjectName("PrimLegend")
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(PrimLegend.sizePolicy().hasHeightForWidth())
        PrimLegend.setSizePolicy(sizePolicy)
        PrimLegend.setMaximumSize(QtCore.QSize(420, 0))
        self.primLegendLayoutContainer = QtWidgets.QVBoxLayout(PrimLegend)
        self.primLegendLayoutContainer.setObjectName("primLegendLayoutContainer")
        self.primLegendLayout = QtWidgets.QGridLayout()
        self.primLegendLayout.setObjectName("primLegendLayout")
        self.primLegendColorHasArcs = QtWidgets.QGraphicsView(PrimLegend)
        self.primLegendColorHasArcs.setMaximumSize(QtCore.QSize(20, 15))
        self.primLegendColorHasArcs.setObjectName("primLegendColorHasArcs")
        self.primLegendLayout.addWidget(self.primLegendColorHasArcs, 0, 0, 1, 1)
        self.primLegendLabelHasArcs = QtWidgets.QLabel(PrimLegend)
        font = QtGui.QFont()
        font.setFamily("Gotham Rounded")
        font.setPointSize(9)
        font.setWeight(50)
        font.setItalic(False)
        font.setBold(False)
        self.primLegendLabelHasArcs.setFont(font)
        self.primLegendLabelHasArcs.setObjectName("primLegendLabelHasArcs")
        self.primLegendLayout.addWidget(self.primLegendLabelHasArcs, 0, 1, 1, 1)
        self.primLegendColorInstance = QtWidgets.QGraphicsView(PrimLegend)
        self.primLegendColorInstance.setMaximumSize(QtCore.QSize(20, 15))
        self.primLegendColorInstance.setObjectName("primLegendColorInstance")
        self.primLegendLayout.addWidget(self.primLegendColorInstance, 0, 2, 1, 1)
        self.primLegendLabelInstance = QtWidgets.QLabel(PrimLegend)
        font = QtGui.QFont()
        font.setFamily("Gotham Rounded")
        font.setPointSize(9)
        font.setWeight(50)
        font.setItalic(False)
        font.setBold(False)
        self.primLegendLabelInstance.setFont(font)
        self.primLegendLabelInstance.setObjectName("primLegendLabelInstance")
        self.primLegendLayout.addWidget(self.primLegendLabelInstance, 0, 3, 1, 1)
        self.primLegendColorMaster = QtWidgets.QGraphicsView(PrimLegend)
        self.primLegendColorMaster.setMaximumSize(QtCore.QSize(20, 15))
        self.primLegendColorMaster.setObjectName("primLegendColorMaster")
        self.primLegendLayout.addWidget(self.primLegendColorMaster, 0, 4, 1, 1)
        self.primLegendLabelMaster = QtWidgets.QLabel(PrimLegend)
        font = QtGui.QFont()
        font.setFamily("Gotham Rounded")
        font.setPointSize(9)
        font.setWeight(50)
        font.setItalic(False)
        font.setBold(False)
        self.primLegendLabelMaster.setFont(font)
        self.primLegendLabelMaster.setObjectName("primLegendLabelMaster")
        self.primLegendLayout.addWidget(self.primLegendLabelMaster, 0, 5, 1, 1)
        self.primLegendColorNormal = QtWidgets.QGraphicsView(PrimLegend)
        self.primLegendColorNormal.setMaximumSize(QtCore.QSize(20, 15))
        self.primLegendColorNormal.setObjectName("primLegendColorNormal")
        self.primLegendLayout.addWidget(self.primLegendColorNormal, 0, 6, 1, 1)
        self.primLegendLabelNormal = QtWidgets.QLabel(PrimLegend)
        font = QtGui.QFont()
        font.setFamily("Gotham Rounded")
        font.setPointSize(9)
        font.setWeight(50)
        font.setItalic(False)
        font.setBold(False)
        self.primLegendLabelNormal.setFont(font)
        self.primLegendLabelNormal.setObjectName("primLegendLabelNormal")
        self.primLegendLayout.addWidget(self.primLegendLabelNormal, 0, 7, 1, 1)
        self.primLegendLayoutContainer.addLayout(self.primLegendLayout)
        self.primLegendLabelContainer = QtWidgets.QVBoxLayout()
        self.primLegendLabelContainer.setObjectName("primLegendLabelContainer")
        self.primLegendLabelDimmed = QtWidgets.QLabel(PrimLegend)
        self.primLegendLabelDimmed.setObjectName("primLegendLabelDimmed")
        self.primLegendLabelContainer.addWidget(self.primLegendLabelDimmed)
        self.primLegendLabelFontsAbstract = QtWidgets.QLabel(PrimLegend)
        self.primLegendLabelFontsAbstract.setObjectName("primLegendLabelFontsAbstract")
        self.primLegendLabelContainer.addWidget(self.primLegendLabelFontsAbstract)
        self.primLegendLabelFontsUndefined = QtWidgets.QLabel(PrimLegend)
        self.primLegendLabelFontsUndefined.setObjectName("primLegendLabelFontsUndefined")
        self.primLegendLabelContainer.addWidget(self.primLegendLabelFontsUndefined)
        self.primLegendLabelFontsDefined = QtWidgets.QLabel(PrimLegend)
        self.primLegendLabelFontsDefined.setObjectName("primLegendLabelFontsDefined")
        self.primLegendLabelContainer.addWidget(self.primLegendLabelFontsDefined)
        self.primLegendLayoutContainer.addLayout(self.primLegendLabelContainer)

        self.retranslateUi(PrimLegend)

    def retranslateUi(self, PrimLegend):
        PrimLegend.setProperty("comment", QtWidgets.QApplication.translate("PrimLegend", "\n"
"     Copyright 2017 Pixar                                                                   \n"
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
        self.primLegendLabelHasArcs.setText(QtWidgets.QApplication.translate("PrimLegend", "HasArcs", None))
        self.primLegendLabelInstance.setText(QtWidgets.QApplication.translate("PrimLegend", "Instance", None))
        self.primLegendLabelMaster.setText(QtWidgets.QApplication.translate("PrimLegend", "Master", None))
        self.primLegendLabelNormal.setText(QtWidgets.QApplication.translate("PrimLegend", "Normal", None))
        self.primLegendLabelDimmed.setText(QtWidgets.QApplication.translate("PrimLegend", "Dimmed colors denote inactive prims", None))
        self.primLegendLabelFontsAbstract.setText(QtWidgets.QApplication.translate("PrimLegend", "Normal font indicates abstract prims(class and children)", None))
        self.primLegendLabelFontsUndefined.setText(QtWidgets.QApplication.translate("PrimLegend", "Italic font indicates undefined prims(declared with over)", None))
        self.primLegendLabelFontsDefined.setText(QtWidgets.QApplication.translate("PrimLegend", "Bold font indicates defined prims(declared with def)", None))

