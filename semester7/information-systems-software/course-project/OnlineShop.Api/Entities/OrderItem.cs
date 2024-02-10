using System.ComponentModel.DataAnnotations.Schema;

namespace OnlineShop.Api.Entities;

public class OrderItem
{
    public int Id { get; set; }

    public required int OrderId { get; set; }

    public required int ProductId { get; set; }

    public required int Quantity { get; set; }

    [ForeignKey("ProductId")]
    public Smartphone Product { get; set; }

    [ForeignKey("OrderId")]
    public Order Order { get; set; }
}