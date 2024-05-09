using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using OnlineShop.Web.Models;

namespace OnlineShow.Web.Pages;

[BindProperties]
public class IndexModel : PageModel
{
    public IEnumerable<Smartphone> Products { get; set; } = new List<Smartphone>();

    public string ErrorMessage { get; set; }

    private readonly HttpClient _httpClient;

    public IndexModel(HttpClient httpClient)
    {
        this._httpClient = httpClient;  
    }

    public async Task OnGetAsync(string? search)
    {
        try
        {
            string requestUrl = search == null ? 
                $"api/Product" : 
                $"api/Product?search={search}";

            var response = await this._httpClient.GetAsync(requestUrl);

            if (response.IsSuccessStatusCode)
            {
                if (response.StatusCode != System.Net.HttpStatusCode.NoContent)
                {
                    Products = await response.Content.ReadFromJsonAsync<IEnumerable<Smartphone>>();
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
}
