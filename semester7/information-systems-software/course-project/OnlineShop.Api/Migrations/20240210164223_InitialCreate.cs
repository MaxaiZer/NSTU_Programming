using System;
using Microsoft.EntityFrameworkCore.Migrations;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace OnlineShop.Api.Migrations
{
    /// <inheritdoc />
    public partial class InitialCreate : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "orders",
                columns: table => new
                {
                    Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    PickupPointId = table.Column<int>(type: "integer", nullable: false),
                    Phone = table.Column<string>(type: "text", nullable: false),
                    Total = table.Column<float>(type: "real", nullable: false),
                    Date = table.Column<DateOnly>(type: "date", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_orders", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "pickup_points",
                columns: table => new
                {
                    Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    City = table.Column<string>(type: "text", nullable: false),
                    Address = table.Column<string>(type: "text", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_pickup_points", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "smartphones",
                columns: table => new
                {
                    Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    ImageUrl = table.Column<string>(type: "text", nullable: false),
                    Model = table.Column<string>(type: "text", nullable: false),
                    OS = table.Column<string>(type: "text", nullable: false),
                    Diagonal = table.Column<float>(type: "real", nullable: false),
                    Cores = table.Column<int>(type: "integer", nullable: false),
                    RAM = table.Column<int>(type: "integer", nullable: false),
                    BatteryCapacity = table.Column<int>(type: "integer", nullable: false),
                    ReleaseYear = table.Column<int>(type: "integer", nullable: false),
                    DefaultPrice = table.Column<float>(type: "real", nullable: false),
                    CurrentPrice = table.Column<float>(type: "real", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_smartphones", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "order_items",
                columns: table => new
                {
                    Id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    OrderId = table.Column<int>(type: "integer", nullable: false),
                    ProductId = table.Column<int>(type: "integer", nullable: false),
                    Quantity = table.Column<int>(type: "integer", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_order_items", x => x.Id);
                    table.ForeignKey(
                        name: "FK_order_items_orders_OrderId",
                        column: x => x.OrderId,
                        principalTable: "orders",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_order_items_smartphones_ProductId",
                        column: x => x.ProductId,
                        principalTable: "smartphones",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.InsertData(
                table: "pickup_points",
                columns: new[] { "Id", "Address", "City" },
                values: new object[,]
                {
                    { 1, "ул. Ленина, 4", "Новосибирск" },
                    { 2, "Юбилейный проспект, 59", "Бердск" }
                });

            migrationBuilder.InsertData(
                table: "smartphones",
                columns: new[] { "Id", "BatteryCapacity", "Cores", "CurrentPrice", "DefaultPrice", "Diagonal", "ImageUrl", "Model", "OS", "RAM", "ReleaseYear" },
                values: new object[,]
                {
                    { 1, 2018, 6, 45999f, 49999f, 4.7f, "/images/iphoneSE.png", "Apple Iphone SE", "iOS 15", 4, 2022 },
                    { 2, 5000, 8, 6499f, 6499f, 6.52f, "/images/redmiA2.png", "Xiaomi Redmi A2+", "Android 12 Go", 3, 2023 },
                    { 3, 5000, 8, 9899f, 9899f, 6.5f, "/images/galaxyA03.png", "Samsung Galaxy A03", "Android 11 Go", 2, 2021 },
                    { 4, 3000, 8, 5699f, 5699f, 6.5f, "/images/nokiaC20.png", "Nokia C20", "Android 11 Go", 2, 2021 },
                    { 5, 5000, 8, 9499f, 9999f, 6.71f, "/images/redmi12C.png", "Xiaomi Redmi 12C", "Android 12", 4, 2023 },
                    { 6, 4000, 4, 4799f, 4799f, 6.6f, "/images/itelA49.png", "Itel A49", "Android 11 Go", 2, 2022 },
                    { 7, 4000, 6, 71999f, 79999f, 6.1f, "/images/iphone13.png", "Apple iPhone 13", "iOS 15", 4, 2021 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_order_items_OrderId",
                table: "order_items",
                column: "OrderId");

            migrationBuilder.CreateIndex(
                name: "IX_order_items_ProductId",
                table: "order_items",
                column: "ProductId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "order_items");

            migrationBuilder.DropTable(
                name: "pickup_points");

            migrationBuilder.DropTable(
                name: "orders");

            migrationBuilder.DropTable(
                name: "smartphones");
        }
    }
}
