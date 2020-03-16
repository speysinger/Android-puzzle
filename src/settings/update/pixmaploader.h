#ifndef PIXMAPLOADER_H
#define PIXMAPLOADER_H

#include <QNetworkAccessManager>
#include <QPixmap>
#include <QEventLoop>
class PixmapLoader : public QObject {
    Q_OBJECT
public:
    PixmapLoader(QObject *parent = 0);
    struct NetworReplyException : public std::invalid_argument{
        NetworReplyException(std::string what) : std::invalid_argument(what) {
        }
    };
    QString getPicPath();
public slots:
    void load(QString imageUrl);
private slots:
    void on_load(QNetworkReply* reply);
signals:
    void loaded(QString);
private:
    QNetworkAccessManager m_manager;
    QString m_pic_path;
    QString picFilePath;
};

#define LOADERPIXMAP Singleton<PixmapLoader>::instance()
#endif // PIXMAPLOADER_H
