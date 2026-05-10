#include "Order.h"

Order::Order(int OrderId, vector<OrderItem> items, string status) {
    this->OrderId = OrderId;
    this->items = items;
    this->status = status;
}

int Order::getOrderId() {
    return OrderId;
}

vector<OrderItem>& Order::getItems() {
    return items;
}

string Order::getStatus() {
    return status;
}

void Order::setStatus(string status) {
    this->status = status;
}
