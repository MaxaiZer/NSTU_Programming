using System.Text;
using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using OnlineShop.Web.Models;

namespace OnlineShow.Web.Pages;

[BindProperties]
public class OrderModel : PageModel
{

    public enum State
    {
        SelectCity,
        SelectAddress,
        OrderComplete
    }

    public State CurState { get; set; } = State.SelectCity;

    public List<string> Cities = new();

    public string SelectedCity { get; set; }

    public List<PickupPoint> PickupPoints = new();

    public int SelectedPickupPointId { get; set; }

    public OrderDetail OrderDetail { get; set; }

    public string Message { get; set; }

    private readonly HttpClient _httpClient;

    public OrderModel(HttpClient httpClient)
    {
        this._httpClient = httpClient;  
    }

    public async Task<IActionResult> OnPostAsync()
    {
        if (CurState == State.SelectCity)
        {
            CurState = State.SelectAddress;
            PickupPoints = await GetPickupPoints();
            PickupPoints = PickupPoints.Where(point => point.City == SelectedCity).ToList();
        } 
 
        return Page();
    }

    public async Task<IActionResult> OnPostCreateOrder()
    {
        string? phone = HttpContext.Session.GetString("phone");
        if (phone == null)
        {
            Message = "Ошибка. Телефон не был сохранён.";
            return Page();
        }

        List<CartItem>? items;

        string? json = HttpContext.Session.GetString("cart");
        if (json == null)
        {
            Message = "Ошибка. Корзина пуста.";
            return Page();
        }

        items = JsonSerializer.Deserialize<List<CartItem>>(json);
        if (items == null)
        {
            Message = "Ошибка десериализации корзины.";
            return Page();
        }

        var order = new OrderRequest{PickupPointId = SelectedPickupPointId, Phone = phone, CartItems = items};
        var jsonContent = JsonSerializer.Serialize(order);
        var stringContent = new StringContent(jsonContent, Encoding.UTF8, "application/json");

        var response = await this._httpClient.PostAsync($"api/Order", stringContent);

        if (!response.IsSuccessStatusCode)
        {
            Message = "Внутренняя ошибка сервера.";
            return Page();
        }

        var idString = await response.Content.ReadAsStringAsync();
    
        if (int.TryParse(idString, out int id))
        {
            response = await this._httpClient.GetAsync($"api/Order/{id}");
            if (response.IsSuccessStatusCode && 
                response.StatusCode != System.Net.HttpStatusCode.NoContent)
            {
                OrderDetail = await response.Content.ReadFromJsonAsync<OrderDetail>();
            }
        }
        else
        {
            Message = "Ошибка получения id заказа.";
            return Page();
        }

        HttpContext.Session.Remove("cart");
        CurState = State.OrderComplete;
        return Page();
    }

    public async Task OnGetAsync()
    {     
        var points = await GetPickupPoints();
        Cities = points.DistinctBy(point => point.City).Select(point => point.City).ToList();
    }

    private async Task<List<PickupPoint>> GetPickupPoints()
    {
        var response = await _httpClient.GetAsync($"api/PickupPoint");
        if (response.IsSuccessStatusCode)
        {
            if (response.StatusCode != System.Net.HttpStatusCode.NoContent)
            {
                return await response.Content.ReadFromJsonAsync<List<PickupPoint>>() ?? new();
            }
        }

        return new();
    }
}
