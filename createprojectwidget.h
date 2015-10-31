#ifndef CREATEPROJECTWIDGET_H
#define CREATEPROJECTWIDGET_H

#include <QWidget>
#include <QString>
namespace Ui {
class CreateProjectWidget;
}

class CreateProjectWidget : public QWidget
{
    Q_OBJECT
    void presentError(QString* errorMessage);
public:
    explicit CreateProjectWidget(QWidget *parent = 0);
    ~CreateProjectWidget();

signals:
    /*!
     *  @param: void
     *   @desc: A signal emitted when the user chooses to save changes
     * @return: void
    */
    void saveChangesClicked();

private slots:

    void on_btnSave_clicked();

private:
    Ui::CreateProjectWidget *ui;
};

#endif // CREATEPROJECTWIDGET_H
