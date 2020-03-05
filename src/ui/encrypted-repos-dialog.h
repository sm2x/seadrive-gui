#ifndef SEAFILE_ENCRYPT_LIBRARY_DIALOG_H
#define SEAFILE_ENCRYPT_LIBRARY_DIALOG_H

#include <jansson.h>

#include <QDialog>
#include <QTableView>
#include <QStackedWidget>
#include <QHeaderView>

class EncryptedRepoInfo {

public:
    QString repo_id;
    QString repo_name;
    bool is_password_set;

    bool operator==(const EncryptedRepoInfo& info) const {
        return repo_id == info.repo_id && repo_name == info.repo_name;
    }

    static  EncryptedRepoInfo fromJSON(const json_t *root);
    static QList<EncryptedRepoInfo> listFromJSON(const json_t *json);

};


class EncryptedReposTableView;
class EncryptedReposTableModel;
class SeafileRpcClient;

class EncryptedReposDialog : public QDialog
{
    Q_OBJECT

public:
    EncryptedReposDialog(QWidget *parent = 0);
    void createEmptyView();

private slots:
    void onModelReset();

private:
    QStackedWidget *stack_;
    QWidget *empty_view_;
    EncryptedReposTableView *table_;
    EncryptedReposTableModel *model_;
};


class EncryptedReposTableView : public QTableView
{
    Q_OBJECT

public:
    EncryptedReposTableView(QWidget *parent=0);
    void resizeEvent(QResizeEvent *event);

signals:
    void sigSetEncRepoPassword(const QString& repo_id, const QString& password);
    void sigClearEncEncRepoPassword(const QString& repo_id);

private slots:
    void onItemDoubleClicked(const QModelIndex& index);

    void onClickSyncAction();
private:
    void createContextMenu();
    void contextMenuEvent(QContextMenuEvent *event);
    QMenu *context_menu_;
    EncryptedRepoInfo enc_repo_info_;
};


class EncryptedReposTableModel: public QAbstractTableModel
{
Q_OBJECT
public:
    EncryptedReposTableModel(QObject *parent=0);

    int rowCount(const QModelIndex& parent=QModelIndex()) const;
    int columnCount(const QModelIndex& parent=QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    EncryptedRepoInfo encRepoInfoAt(int i) const { return  enc_repo_infos_[i]; }

    void onResize(const QSize& size);

public slots:
    void updateEncryptRepoList();
    void slotSetEncRepoPassword(const QString& repo_id, const QString& password);
    void slotClearEncRepoPassword(const QString& repo_id);

private:

    QList<EncryptedRepoInfo> enc_repo_infos_;
    SeafileRpcClient *rpc_client_;
    int repo_name_column_width_;
    int repo_status_column_width_;
};

#endif // SEAFILE_ENCRYPT_LIBRARY_DIALOG_H
