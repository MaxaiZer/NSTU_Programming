using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using OnlineShop.Web.Models;

namespace OnlineShow.Web.Pages;

[BindProperties]
public class ProductModel : PageModel
{
    public Smartphone Product { get; set; } = new Smartphone();

    public string ErrorMessage { get; set; }

    private readonly HttpClient httpClient;

    public ProductModel(HttpClient httpClient)
    {
        this.httpClient = httpClient;
    }

    public async Task OnGetAsync(int id)
    {
        try
        {
            var response = await this.httpClient.GetAsync($"api/Product/{id}");

            if (response.IsSuccessStatusCode)
            {
                if (response.StatusCode != System.Net.HttpStatusCode.NoContent)
                {
                    Product = await response.Content.ReadFromJsonAsync<Smartphone>();
                }
            }
            else
            {
                var message = await response.Content.ReadAsStringAsync();
                ErrorMessage = $"Http status code: {response.StatusCode} message: {message}";
            }

        }
        catch (Exception ex)
        {
            ErrorMessage = ex.Message;
        }
    }

    public IActionResult OnPostAddToCart(int productId)
    {
        List<CartItem> cart = new();
        string? json = HttpContext.Session.GetString("cart");
        if (json != null)
        {
            cart = JsonSerializer.Deserialize<List<CartItem>>(json) ?? new();
        }
        var item = cart.Find(item => item.ProductId == productId);
        if (item == null)
            cart.Add(new CartItem{ProductId = productId, Quantity = 1});
        else
            item.Quantity++;
        
        HttpContext.Session.SetString("cart", JsonSerializer.Serialize(cart));
        return RedirectToPage("Cart");
    }
}
