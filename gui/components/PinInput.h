#ifndef PININPUT_H
#define PININPUT_H

#include <QString>
#include <QWidget>

class QLineEdit;
class QLabel;
class QMouseEvent;

class PinInput : public QWidget
{
    Q_OBJECT

public:
    explicit PinInput(QWidget *parent = nullptr);

    QString passcode() const;
    bool isComplete() const;
    void clear();

signals:
    void passcodeCompleted(const QString &passcode);
    void submitKeyPressed(const QString &passcode);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLineEdit *input;
    QLabel *pinBoxes[4];

    void setupUI();
    void updatePinBoxes();
};

#endif // PININPUT_H