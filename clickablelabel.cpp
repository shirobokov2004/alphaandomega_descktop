#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent) {

}
ClickableLabel::~ClickableLabel() {
    this->deleteLater();
}
void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
