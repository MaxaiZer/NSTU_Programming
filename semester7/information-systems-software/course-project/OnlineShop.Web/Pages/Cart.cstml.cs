using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using OnlineShop.Web.Models;

namespace OnlineShow.Web.Pages;

[BindProperties]
public class CartModel : PageModel
{
    public IEnumerable<(Smartphone, int)> ProductsAndQuantities { get; set; } = new List<(Smartphone, int)>();

    public string ErrorMessage { get; set; }

    private readonly HttpClient _httpClient;

    public CartModel(HttpClient httpClient)
    {
        this._httpClient = httpClient;  
    }

    public async Task OnGetAsync()
    {
        List<CartItem> cart = new();
        string? json = HttpContext.Session.GetString("cart");
        if (json != null)
        {
            cart = JsonSerializer.Deserialize<List<CartItem>>(json) ?? new();
        }

        List<(Smartphone, int)> _productsAndQuantities = new();

        try
        {
            foreach (var item in cart)
            {
                var response = await this._httpClient.GetAsync($"api/Product/{item.ProductId}");
                if (response.IsSuccessStatusCode)
                {
                    if (response.StatusCode != System.Net.HttpStatusCode.NoContent)
                    {
                        var Product = await response.Content.ReadFromJsonAsync<Smartphone>();
                        _productsAndQuantities.Add((Product, item.Quantity));  
                    }
                }
                else
                {
                    var message = await response.Content.ReadAsStringAsync();
                    ErrorMessage = $"Http status code: {response.StatusCode} message: {message}";
                }
            }
        }
        catch (Exception ex)
        {
            ErrorMessage = ex.Message;
        }

        ProductsAndQuantities = _productsAndQuantities;
    }

    public IActionResult OnPostRemoveFromCart(int productId)
    {
        List<CartItem> cart = new();
        string? json = HttpContext.Session.GetString("cart");
        if (json != null)
        {
            cart = JsonSerializer.Deserialize<List<CartItem>>(json) ?? new();
            cart.Remove(cart.Single(item => item.ProductId == productId));
            HttpContext.Session.SetString("cart", JsonSerializer.Serialize(cart));
        }

        return RedirectToPage("Cart");
    }
    public IActionResult OnPostCheckout()
    {
        return RedirectToPage("PhoneCheck");
    }

}
