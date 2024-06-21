#ifndef INPUT_H
#define INPUT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class Input : public QLineEdit
{
    Q_OBJECT
public:
    explicit Input(QWidget* parent = nullptr);
    ~Input();
    bool isPassword();
    void setPassword(bool);
private:
    inline static QString m_style = "QLineEdit{border: 2px solid rgb(84,84,84); border-radius: 15px; background: #1F1F21; color: rgba(255, 255, 255, 0.6); font-size: 16px; padding: 9px 15px;}"
                                  "QLineEdit:focus{border: 2px solid rgba(224, 169, 110, 1);}";
};

#endif // INPUT_H
