#include "dialog.h"
#include "ui_dialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>

typedef struct {
    QString     mean      ;    // 含义
    QLabel      *pLabel   ;    // label控件
    QString     pattern   ;    // 正则表达式字符
    QRegExp     regExp    ;    // 正则表达式
    QLineEdit   *pLineEdit;    // lineedit控件
} TestQRegExp;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QGridLayout *pGridLayout = new QGridLayout(this);
    this->setLayout(pGridLayout);

    TestQRegExp Tre[32];


    int count = 0;
    Tre[count].mean      = "0~9";                   // 含义
    Tre[count].pattern   = "[0-9]";                 // 正则表达式
    count++;
    Tre[count].mean      = "-9~9";                   // 含义
    Tre[count].pattern   = "[0-9]|-[1-9]";           // 正则表达式
    count++;
    Tre[count].mean      = "0~99";                  // 含义
    Tre[count].pattern   = "0|[1-9]\\d{0,1}";       // 正则表达式    "\d"代表任意数字（由于C++所以用"\\"表示"\"）
    count++;
    Tre[count].mean      = "0~999";                 // 含义
    Tre[count].pattern   = "0|[1-9]\\d{0,2}";       // 正则表达式
    count++;
    Tre[count].mean      = "0~9999";                // 含义
    Tre[count].pattern   = "0|[1-9]\\d{0,3}";       // 正则表达式
    count++;
    Tre[count].mean      = "00~99";                 // 含义
    Tre[count].pattern   = "[0-9]\\d{0,1}";         // 正则表达式
    count++;
    Tre[count].mean      = "000~999";               // 含义
    Tre[count].pattern   = "[0-9]\\d{0,2}";         // 正则表达式
    count++;
    Tre[count].mean      = "0000~9999";             // 含义
    Tre[count].pattern   = "[0-9]\\d{0,3}";         // 正则表达式
    count++;
    Tre[count].mean      = "0.00~1,两位小数";           // 含义（不能输入1.00）
    Tre[count].pattern   = "1|([0-0]{1}[.][0-9]{1,2})";// 正则表达式
    count++;
    Tre[count].mean      = "0.00~1.00,两位小数";                          // 含义
    Tre[count].pattern   = "([1]{1}[.][0]{1,2})|([0-0]{1}[.][0-9]{1,2})";// 正则表达式
    count++;
    Tre[count].mean      = "0.0~10,一位小数";               // 含义（不能输入10.0）
    Tre[count].pattern   = "^?(10|[0-0]?\\d(\\.\\d{1})?)$";// 正则表达式
    count++;
    Tre[count].mean      = "-999.99~999.99";               // 含义（不能输入10.0）
    Tre[count].pattern   = "^[-]?[\\d]{1,3}[.][\\d]{0,2}$";// 正则表达式



    for(int countId = 0; countId < 16; countId++) {
        Tre[countId].pLabel    = new QLabel(Tre[countId].pattern);      // Lable文字显示正则表达式的公式
        Tre[countId].pLineEdit = new QLineEdit(this);                   // 实例化输入框
        Tre[countId].pLineEdit->setPlaceholderText(Tre[countId].mean);  // 输入框背景文字显示含义范围
        Tre[countId].regExp   .setPattern(Tre[countId].pattern);        // 设置正则表达式公式值
        Tre[countId].pLineEdit->setValidator(new QRegExpValidator(Tre[countId].regExp, this));  // 设置正则表达式
        pGridLayout->addWidget(Tre[countId].pLabel   , countId, 0);     // 将Label插入布局管理器
        pGridLayout->addWidget(Tre[countId].pLineEdit, countId, 1);     // 将输入框插入布局管理器
    }

}

Dialog::~Dialog()
{
    delete ui;
}

