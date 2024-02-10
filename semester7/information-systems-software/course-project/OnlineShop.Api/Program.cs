using System.Data;
using Microsoft.EntityFrameworkCore;
using Npgsql;
using Microsoft.Net.Http.Headers;
using OnlineShop.Api.Data;
using OnlineShop.Api.Repositories;
using OnlineShop.Api.Repositories.Contracts;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

builder.Services.AddControllers();
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddScoped<IProductRepository, SmartphoneRepository>();
builder.Services.AddScoped<IOrderItemRepository, OrderItemRepository>();
builder.Services.AddScoped<IPickupPointRepository, PickupPointRepository>();
builder.Services.AddScoped<IOrderRepository, OrderRepository>();
builder.Services.AddScoped<IOrderService, OrderService>();

builder.Services.AddDbContext<ShopDbContext>(options =>
    options.UseNpgsql(builder.Configuration.GetConnectionString("DefaultConnection")));

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseCors(policy =>
    policy.WithOrigins("http://localhost:5021", "https://localhost:5021")
    .AllowAnyMethod()
    .WithHeaders(HeaderNames.ContentType)
);

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();
