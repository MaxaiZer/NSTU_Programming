namespace OnlineShop.Web.Models;

public class OrderDetail
{
    public int Id { get; set; }

    public required string Phone { get; set; }

    public required PickupPoint PickupPoint { get; set; }

    public required List<string> ItemsNames { get; set; }

    public required List<int> ItemsQuantities { get; set; }

    public required float Total { get; set; }

    public required DateOnly Date { get; set; }
}
