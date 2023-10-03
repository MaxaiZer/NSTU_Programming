using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace lab3.Pages;

public class DeleteModel : PageModel
{
    private IDisciplineRepository _repository;
    public DeleteModel(IDisciplineRepository repository)
    {
        _repository = repository;
    }

    public IActionResult OnGet(int id)
    {
        _repository.Delete(id);
        return Redirect("~/");
    }
}