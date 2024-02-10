using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using OnlineShop.Web.Models;

namespace OnlineShow.Web.Pages;

[BindProperties]
public class PhoneCheckModel : PageModel
{

    public enum State
    {
        PhoneInput,
        Confirmation
    }

    public State CurState { get; set; } = State.PhoneInput;


    [RegularExpression(@"^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$", 
         ErrorMessage = "Неправильный номер телефона.")]
    public string PhoneNumber { get; set; }

    public int? Code { get; set; }

    private readonly HttpClient _httpClient;

    public PhoneCheckModel(HttpClient httpClient)
    {
        this._httpClient = httpClient;  
    }

    public async Task<IActionResult> OnPostAsync()
    {
        if (CurState == State.PhoneInput)
            return OnPostPhoneInput();
        if (CurState == State.Confirmation)
            return OnPostCodeInput();
 
        return Page();
    }

    public IActionResult OnPostPhoneInput()
    {
        if (ModelState.IsValid)
        {
            HttpContext.Session.SetString("phone", PhoneNumber);
            CurState = State.Confirmation;
        }

        return Page();
    }

    public IActionResult OnPostCodeInput()
    {

        //check code here

        if (Code == 0)
            return RedirectToPage("Order");
        else
            ModelState.AddModelError("Code", "Неправильный код");

        return Page();
    }

    public async Task OnGetAsync()
    {

    }
}
