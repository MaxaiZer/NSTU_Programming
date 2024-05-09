namespace OnlineShop.Web.Models;

public class Smartphone
{
    public int Id { get; set; }

    public string ImageUrl { get; set; }

    public string Model { get; set; }

    public string OS { get; set; }

    public float Diagonal { get; set; }

    public int Cores { get; set; }

    public int RAM { get; set; }

    public int BatteryCapacity { get; set; }

    public int ReleaseYear { get; set; }

    public float DefaultPrice { get; set; }

    public float CurrentPrice { get; set; }
}