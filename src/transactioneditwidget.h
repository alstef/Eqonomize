/***************************************************************************
 *   Copyright (C) 2006-2008, 2014, 2016 by Hanna Knutsson                 *
 *   hanna_k@fmgirl.com                                                    *
 *                                                                         *
 *   This file is part of Eqonomize!.                                      *
 *                                                                         *
 *   Eqonomize! is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   Eqonomize! is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with Eqonomize!. If not, see <http://www.gnu.org/licenses/>.    *
 ***************************************************************************/

#ifndef TRANSACTION_EDIT_WIDGET_H
#define TRANSACTION_EDIT_WIDGET_H

#include <QHash>
#include <QString>
#include <QVector>
#include <QWidget>
#include <QDialog>
#include <QDateEdit>

class QCheckBox;
class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
class QHBoxLayout;

class EqonomizeDateEdit;

class Budget;
class Account;
class AccountComboBox;
class EqonomizeValueEdit;
class Security;
class Transaction;
class Transactions;
class MultiAccountTransaction;

typedef enum {
	SECURITY_ALL_VALUES,
	SECURITY_SHARES_AND_QUOTATION,
	SECURITY_VALUE_AND_SHARES,
	SECURITY_VALUE_AND_QUOTATION
} SecurityValueDefineType;

class TransactionEditWidget : public QWidget {

	Q_OBJECT

	public:

		TransactionEditWidget(bool auto_edit, bool extra_parameters, int transaction_type, bool split, bool transfer_to, Security *security, SecurityValueDefineType security_value_type, bool select_security, Budget *budg, QWidget *parent = 0, bool allow_account_creation = false, bool multiaccount = false, bool withloan = false);
		void setTransaction(Transaction *trans);
		void setMultiAccountTransaction(MultiAccountTransaction *split);
		void setTransaction(Transaction *strans, const QDate &date);
		void updateFromAccounts(Account *exclude_account = NULL);
		void updateToAccounts(Account *exclude_account = NULL);
		void updateAccounts(Account *exclude_account = NULL);
		void transactionsReset();		
		void setCurrentToItem(int index);
		void setCurrentFromItem(int index);
		void setAccount(Account *account);
		int currentToItem();
		int currentFromItem();
		void focusDescription();
		QHBoxLayout *bottomLayout();
		void transactionRemoved(Transaction *trans);
		void transactionAdded(Transaction *trans);
		void transactionModified(Transaction *trans);
		bool modifyTransaction(Transaction *trans);
		Transaction *createTransaction();
		Transactions *createTransactionWithLoan();
		bool validValues(bool ask_questions = false);
		void setValues(QString description_value, double value_value, double quantity_value, QDate date_value, Account *from_account_value, Account *to_account_value, QString payee_value, QString comment_value);
		QDate date();
		QString description() const;
		QString payee() const;
		QString comments() const;
		double value() const;
		double quantity() const;
		Account *fromAccount() const;
		Account *toAccount() const;
		Security *selectedSecurity();
		void setMaxShares(double max);
		void setMaxSharesDate(QDate quotation_date);
		bool checkAccounts();
		void currentDateChanged(const QDate &olddate, const QDate &newdate);

	protected:

		QHash<QString, Transaction*> default_values;
		QHash<QString, Transaction*> default_payee_values;
		QHash<Account*, Transaction*> default_category_values;
		int transtype;
		bool description_changed, payee_changed;
		Budget *budget;
		Security *security;
		bool b_autoedit, b_sec, b_extra;
		bool value_set, shares_set, sharevalue_set;
		QDate shares_date;
		bool b_create_accounts;

		QLineEdit *descriptionEdit, *lenderEdit, *payeeEdit, *commentsEdit;
		AccountComboBox *fromCombo, *toCombo;
		QComboBox *securityCombo;
		EqonomizeValueEdit *valueEdit, *downPaymentEdit, *sharesEdit, *quotationEdit, *quantityEdit;
		QPushButton *maxSharesButton;
		EqonomizeDateEdit *dateEdit;
		QHBoxLayout *bottom_layout;

	signals:

		void addmodify();
		void dateChanged(const QDate&);
		void accountAdded(Account*);
		void multipleAccountsRequested();
		void newLoanRequested();

	public slots:

		void newFromAccount();
		void newToAccount();
		void fromActivated();
		void toActivated();
		void focusDate();
		void valueChanged(double);
		void securityChanged();
		void sharesChanged(double);
		void quotationChanged(double);
		void descriptionChanged(const QString&);
		void setDefaultValue();
		void payeeChanged(const QString&);
		void setDefaultValueFromPayee();
		void setDefaultValueFromCategory();
		void maxShares();

};

class TransactionEditDialog : public QDialog {

	Q_OBJECT

	public:

		TransactionEditDialog(bool extra_parameters, int transaction_type, bool split, bool transfer_to, Security *security, SecurityValueDefineType security_value_type, bool select_security, Budget *budg, QWidget *parent, bool allow_account_creation = false, bool multiaccount = false, bool withloan = false);
		TransactionEditWidget *editWidget;

	protected slots:

		void accept();

};

class MultipleTransactionsEditDialog : public QDialog {

	Q_OBJECT

	public:

		MultipleTransactionsEditDialog(bool extra_parameters, int transaction_type, Budget *budg, QWidget *parent = 0, bool allow_account_creation = false);
		void setTransaction(Transaction *trans);
		void setTransaction(Transaction *strans, const QDate &date);
		void updateAccounts();
		bool modifyTransaction(Transaction *trans, bool change_parent = false);
		bool validValues();
		bool checkAccounts();
		QDate date();

		QCheckBox *descriptionButton, *valueButton, *categoryButton, *dateButton, *payeeButton;

	protected:

		int transtype;
		Budget *budget;
		bool b_extra;
		bool b_create_accounts;
		QVector<Account*> categories;
		QLineEdit *descriptionEdit, *payeeEdit;
		AccountComboBox *categoryCombo;
		EqonomizeValueEdit *valueEdit;
		QDateEdit *dateEdit;
		Account *added_account;

	protected slots:

		void newCategory();
		void accept();

};

class EqonomizeDateEdit : public QDateEdit {

	Q_OBJECT

	public:
	
		EqonomizeDateEdit(QWidget *parent);
	
	protected slots:
	
		void keyPressEvent(QKeyEvent *event);
		
	signals:
	
		void returnPressed();

};


#endif

