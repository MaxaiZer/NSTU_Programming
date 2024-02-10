namespace OnlineShop.Web.Models;

public class OrderRequest
{
    public required int PickupPointId { get; set; }

    public required string Phone { get; set;}

    public required List<CartItem> CartItems { get; set; }
}