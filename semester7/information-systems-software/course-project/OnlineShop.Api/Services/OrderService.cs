using OnlineShop.Api.Dto;
using OnlineShop.Api.Entities;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Repositories;

public class OrderService : IOrderService
{
    protected readonly IOrderRepository _orderRepository;
    protected readonly IOrderItemRepository _orderItemRepository;
    protected readonly IProductRepository _productRepository;
    protected readonly IPickupPointRepository _pickupPointRepository;

    public OrderService(IOrderRepository orderRepository, 
                        IOrderItemRepository orderItemRepository,
                        IProductRepository productRepository,
                        IPickupPointRepository pickupPointRepository)
    {
       _orderRepository = orderRepository;
       _orderItemRepository = orderItemRepository;
       _productRepository = productRepository;
       _pickupPointRepository = pickupPointRepository;
    }

    public int CreateOrder(OrderDto order)
    {
        float sum = 0;
        foreach (var item in order.CartItems)
        {
            Smartphone product = _productRepository.GetById(item.ProductId)
                ?? throw new Exception("Wrong product id");

            sum += product.CurrentPrice;
        }

        Order newOrder = new Order { PickupPointId = order.PickupPointId, Total = sum, Phone = order.Phone, Date = DateOnly.FromDateTime(DateTime.Now)};
        _orderRepository.Add(newOrder);
        _orderRepository.Save();

        foreach (var item in order.CartItems)
            _orderItemRepository.Add(new OrderItem{ ProductId = item.ProductId, Quantity = item.Quantity, OrderId = newOrder.Id });

        _orderItemRepository.Save();
        return newOrder.Id;
    }

    public OrderDetailDto GetOrderDetailById(int orderId)
    {
        Order order = _orderRepository.GetById(orderId) 
            ?? throw new ArgumentException("Wrong order id");

        PickupPoint point = _pickupPointRepository.GetById(order.PickupPointId)
            ?? throw new Exception("Wrong pickup point id in order");

        List<OrderItem> items = _orderItemRepository.GetByOrderId(order.Id);

        return new OrderDetailDto 
            { 
                Id = order.Id, 
                Phone = order.Phone, 
                Total = order.Total, 
                PickupPoint = point, 
                ItemsNames = items.Select
                    (item => _productRepository.GetById(item.ProductId).Model).ToList(),
                ItemsQuantities = items.Select(item => item.Quantity).ToList(),
                Date = order.Date
            };
    }
}