using Microsoft.EntityFrameworkCore;
using OnlineShop.Api.Entities;

namespace OnlineShop.Api.Data;

public class ShopDbContext : DbContext
{

    public DbSet<Smartphone> Smartphones { get; set; }

    public DbSet<Order> Orders { get; set; }

    public DbSet<OrderItem> OrderItems { get; set; }

    public DbSet<PickupPoint> PickupPoints { get; set; }

    public ShopDbContext(DbContextOptions<ShopDbContext> options) : base(options)
    {

    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);

        modelBuilder.Entity<Smartphone>().ToTable("smartphones");
        modelBuilder.Entity<Order>().ToTable("orders");
        modelBuilder.Entity<OrderItem>().ToTable("order_items");
        modelBuilder.Entity<PickupPoint>().ToTable("pickup_points");

        modelBuilder.Entity<Smartphone>().HasData(
        new
        {
            Id = 1,
            ImageUrl = "/images/iphoneSE.png",
            Model = "Apple Iphone SE",
            OS = "iOS 15",
            Diagonal = 4.7f,
            Cores = 6,
            RAM = 4,
            BatteryCapacity = 2018,
            ReleaseYear = 2022,
            DefaultPrice = 49999f,
            CurrentPrice = 45999f
        },
        new
        {
            Id = 2,
            ImageUrl = "/images/redmiA2.png",
            Model = "Xiaomi Redmi A2+",
            OS = "Android 12 Go",
            Diagonal = 6.52f,
            Cores = 8,
            RAM = 3,
            BatteryCapacity = 5000,
            ReleaseYear = 2023,
            DefaultPrice = 6499f,
            CurrentPrice = 6499f
        },
        new
        {
            Id = 3,
            BatteryCapacity = 5000,
            Cores = 8,
            CurrentPrice = 9899f,
            DefaultPrice = 9899f,
            Diagonal = 6.5f,
            ImageUrl = "/images/galaxyA03.png",
            Model = "Samsung Galaxy A03",
            OS = "Android 11 Go",
            RAM = 2,
            ReleaseYear = 2021
        },
        new
        {
            Id = 4,
            BatteryCapacity = 3000,
            Cores = 8,
            CurrentPrice = 5699f,
            DefaultPrice = 5699f,
            Diagonal = 6.5f,
            ImageUrl = "/images/nokiaC20.png",
            Model = "Nokia C20",
            OS = "Android 11 Go",
            RAM = 2,
            ReleaseYear = 2021
        },
        new
        {
            Id = 5,
            BatteryCapacity = 5000,
            Cores = 8,
            CurrentPrice = 9499f,
            DefaultPrice = 9999f,
            Diagonal = 6.71f,
            ImageUrl = "/images/redmi12C.png",
            Model = "Xiaomi Redmi 12C",
            OS = "Android 12",
            RAM = 4,
            ReleaseYear = 2023
        },
        new
        {
            Id = 6,
            BatteryCapacity = 4000,
            Cores = 4,
            CurrentPrice = 4799f,
            DefaultPrice = 4799f,
            Diagonal = 6.6f,
            ImageUrl = "/images/itelA49.png",
            Model = "Itel A49",
            OS = "Android 11 Go",
            RAM = 2,
            ReleaseYear = 2022
        },
        new
        {
            Id = 7,
            BatteryCapacity = 4000,
            Cores = 6,
            CurrentPrice = 71999f,
            DefaultPrice = 79999f,
            Diagonal = 6.1f,
            ImageUrl = "/images/iphone13.png",
            Model = "Apple iPhone 13",
            OS = "iOS 15",
            RAM = 4,
            ReleaseYear = 2021
        }
        );

        modelBuilder.Entity<PickupPoint>().HasData(
        new
        {
            Id = 1,
            City = "Новосибирск",
            Address = "ул. Ленина, 4"
        },
        new {
            Id = 2,
            City = "Бердск",
            Address = "Юбилейный проспект, 59"
        }
        );
    }

}
