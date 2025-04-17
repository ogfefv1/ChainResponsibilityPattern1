
#include <iostream>

using namespace std;

/*
        Ïàòòåðí Chain of Responsibility (Öåïî÷êà Îáÿçàííîñòåé) ïîçâîëÿåò îòäåëèòü îòïðàâèòåëÿ çàïðîñà îò åãî ïîëó÷àòåëÿ,
        ïðåäîñòàâëÿÿ âîçìîæíîñòü íåñêîëüêèì êëàññàì–îáðàáîò÷èêàì îïðåäåëèòü, êòî èç íèõ ìîæåò äàííûé çàïðîñ îáðàáîòàòü.
        Òîò, êòî èíèöèèðóåò çàïðîñ, êàê ïðàâèëî, íå îáëàäàåò èíôîðìàöèåé î òîì, êòî èìåííî èç êëàññîâ, ïîòåíöèàëüíî èìåþùèé
        òàêóþ âîçìîæíîñòü, äàííûé çàïðîñ â êîíå÷íîì èòîãå îáðàáîòàåò.
        Â òàêîé ñõåìå ñóùåñòâóåò íåñêîëüêî êëàññîâ – Handler-îâ (îáðàáîò÷èêîâ), êàæäûé èç êîòîðûõ íàäåë¸í ñâîèìè îãðàíè÷åííûìè
        âîçìîæíîñòÿìè îáðàáîòêè ïîäîáíûõ çàïðîñîâ. Ïðè÷¸ì ýòè îáúåêòû - Handler-û âûñòðàèâàþòñÿ â öåïî÷êó (îò ñàìûõ ñëàáûõ äî ñàìûõ ñèëüíûõ)
        è êàæäûé èç íèõ çíàåò, êîìó îí ïåðåáðîñèò çàïðîñ â òîì ñëó÷àå, åñëè ñàì íå ñìîæåò ñïðàâèòüñÿ ñ åãî îáðàáîòêîé.
        Ïîñëåäíèé â öåïî÷êå Handler, êàê ïðàâèëî, îáëàäàþùèé ñàìûìè âûñîêèìè âîçìîæíîñòÿìè, åñëè ñàì íå ìîæåò îáðàáîòàòü çàïðîñ,
        ïðåäîñòàâëÿåò êàêîå-òî ïîâåäåíèå ïî óìîë÷àíèþ èëè ãåíåðèðóåò èñêëþ÷åíèå.
*/

class Receiver
{
    // банковские переводы
    bool BankTransfer;
    // денежные переводы - WesternUnion, Unistream
    bool MoneyTransfer;
    // перевод через PayPal
    bool PayPalTransfer;
    // перевод через криптовалюту
    bool CryptoTransfer;
    // перевод наличными
    bool CashTransfer;
public:
    Receiver(bool bt, bool mt, bool ppt, bool ct, bool cash)
    {
        BankTransfer = bt;
        MoneyTransfer = mt;
        PayPalTransfer = ppt;
        CryptoTransfer = ct;
        CashTransfer = cash;
    }

    bool GetBankTransfer()
    {
        return BankTransfer;
    }
    void SetBankTransfer(bool BankTransfer)
    {
        this->BankTransfer = BankTransfer;
    }

    bool GetMoneyTransfer()
    {
        return MoneyTransfer;
    }
    void SetMoneyTransfer(bool MoneyTransfer)
    {
        this->MoneyTransfer = MoneyTransfer;
    }

    bool GetPayPalTransfer()
    {
        return PayPalTransfer;
    }
    void SetPayPalTransfer(bool PayPalTransfer)
    {
        this->PayPalTransfer = PayPalTransfer;
    }

    bool GetCryptoTransfer()
    {
        return CryptoTransfer;
    }
    void SetCryptoTransfer(bool CryptoTransfer)
    {
        this->CryptoTransfer = CryptoTransfer;
    }

    bool GetCashTransfer()
    {
        return CashTransfer;
    }
    void SetCashTransfer(bool CashTransfer)
    {
        this->CashTransfer = CashTransfer;
    }
};

class PaymentHandler abstract
{
protected:
    PaymentHandler* Successor;
public:
    PaymentHandler* GetHandler()
    {
        return Successor;
    }
    void SetHandler(PaymentHandler* Successor)
    {
        this->Successor = Successor;
    }
    virtual void Handle(Receiver* receiver) abstract;
};

// банковский перевод
class BankPaymentHandler : public PaymentHandler
{
public:
    void Handle(Receiver* receiver) override
    {
        if (receiver->GetBankTransfer())
            cout << "Bank transfer\n";
        else if (Successor != nullptr)
            Successor->Handle(receiver);
    }
};

// переводы с помощью системы денежных переводов типа WesternUnion или Unistream
class MoneyPaymentHandler : public PaymentHandler
{
public:
    void Handle(Receiver* receiver) override
    {
        if (receiver->GetMoneyTransfer())
            cout << "Transfer through money transfer systems\n";
        else if (Successor != nullptr)
            Successor->Handle(receiver);
    }
};

// система онлайн-платежей PayPal
class PayPalPaymentHandler : public PaymentHandler
{
public:
    void Handle(Receiver* receiver) override
    {
        if (receiver->GetPayPalTransfer())
            cout << "Transfer via paypal\n";
        else if (Successor != nullptr)
            Successor->Handle(receiver);
    }
};

// система криптовалютных переводов
class CryptoPaymentHandler : public PaymentHandler
{
public:
    void Handle(Receiver* receiver) override
    {
        if (receiver->GetCryptoTransfer())
            cout << "Transfer via cryptocurrency\n";
        else if (Successor != nullptr)
            Successor->Handle(receiver);
    }
};

// наличные переводы
class CashPaymentHandler : public PaymentHandler
{
public:
    void Handle(Receiver* receiver) override
    {
        if (receiver->GetCashTransfer())
            cout << "Transfer via cash\n";
        else if (Successor != nullptr)
            Successor->Handle(receiver);
    }
};

// Необходимо отправить определённую сумму денег, но мы не знаем, какой способ доступен
void Request(PaymentHandler* h, Receiver* receiver)
{
    h->Handle(receiver);
}

int main()
{
    PaymentHandler* bankPaymentHandler = new BankPaymentHandler();
    PaymentHandler* cashPaymentHandler = new CashPaymentHandler();
    PaymentHandler* moneyPaymentHandler = new MoneyPaymentHandler();
    PaymentHandler* cryptoPaymentHandler = new CryptoPaymentHandler();
    PaymentHandler* paypalPaymentHandler = new PayPalPaymentHandler();

    // PayPal → Crypto → MoneyPay → Cash → BankPayment
    paypalPaymentHandler->SetHandler(cryptoPaymentHandler);
    cryptoPaymentHandler->SetHandler(moneyPaymentHandler);
    moneyPaymentHandler->SetHandler(cashPaymentHandler);
    cashPaymentHandler->SetHandler(bankPaymentHandler);

    Receiver* receiver = new Receiver(false, false, true, false, false); // PayPal
    Request(paypalPaymentHandler, receiver);
    delete receiver;

    receiver = new Receiver(false, false, false, true, false); // Crypto
    Request(paypalPaymentHandler, receiver);
    delete receiver;

    receiver = new Receiver(false, true, false, false, false); // MoneyPay
    Request(paypalPaymentHandler, receiver);
    delete receiver;

    receiver = new Receiver(false, false, false, false, true); // Cash
    Request(paypalPaymentHandler, receiver);
    delete receiver;

    receiver = new Receiver(true, false, false, false, false); // Bank
    Request(paypalPaymentHandler, receiver);
    delete receiver;

    delete bankPaymentHandler;
    delete cashPaymentHandler;
    delete moneyPaymentHandler;
    delete cryptoPaymentHandler;
    delete paypalPaymentHandler;

    system("pause");
    return 0;
}
