
#ifndef _0_MAIN__WINDOW__
#define _0_MAIN__WINDOW__

#include <QWidget>
#include <QString>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    /* 类型概念定义 */
    typedef MainWindow ThisType ;
    typedef QWidget    SuperType;
    class   ThisPrivate ;

    /* 构造函数 */
    explicit MainWindow( QWidget *  );
    MainWindow():MainWindow(nullptr){}
    /* 析构函数 */
    ~MainWindow();

private:
    friend class ThisPrivate ;
    ThisPrivate * thisp = nullptr;
public slots:
    void setPath(const QString & arg_path);
    void setViewPicture(const QString & arg_picture);
    void updatePath();
	void eval( const QString & );
	void selectedChanged( const QStringList & );
	void scrollTo(int);
	void scrolltoNextPicture(int/* the value never use */);
protected:
	void keyPressEvent(QKeyEvent * e) override;
};


#endif

