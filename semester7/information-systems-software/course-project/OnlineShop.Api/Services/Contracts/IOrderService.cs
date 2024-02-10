using OnlineShop.Api.Dto;

namespace OnlineShop.Api.Repositories.Contracts;

public interface IOrderService
{
    public int CreateOrder(OrderDto order);

    public OrderDetailDto GetOrderDetailById(int orderId);
}