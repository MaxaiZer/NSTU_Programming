using Microsoft.AspNetCore.Mvc;
using OnlineShop.Api.Dto;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Controllers;

[ApiController]
[Route("api/[controller]")]
public class OrderController : ControllerBase
{
    private IOrderService _orderService;

    public OrderController(IOrderService service)
    {
        _orderService = service;
    }

    [HttpPost]
    public IActionResult Add([FromBody] OrderDto order)
    {
        int id = _orderService.CreateOrder(order);
        return Ok(id);
    }

    [HttpGet("{id}")]
    public IActionResult GetOrderDetail(int id)
    {
        return new JsonResult(_orderService.GetOrderDetailById(id));
    }
}