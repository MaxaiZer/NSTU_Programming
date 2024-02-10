namespace OnlineShop.Web.Models;

public class PickupPoint
{
    public int Id { get; set; }

    public required string City { get; set; }

    public required string Address { get; set; }
}