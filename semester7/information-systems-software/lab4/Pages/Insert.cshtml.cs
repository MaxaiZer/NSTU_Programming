using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace lab3.Pages;

[BindProperties]
public class InsertModel : PageModel
{
    public Discipline Discipline { get; set; } = new Discipline(); //иначе в post не будет передано значение id из input при вставке -> ModelState is invalid
    
    public bool IsUpdate { get; set; }

    public string? Message { get; set; }

    private IDisciplineRepository _repository;
    public InsertModel(IDisciplineRepository repository)
    {
        _repository = repository;
    }

    public void OnGet(int? id)
    {
        if (id == null) return;

        IsUpdate = true;
        Discipline = _repository.GetById((int)id);
    }

    public IActionResult OnPost() 
    {
        if (!ModelState.IsValid)
            return Page();

        try 
        {
            if (IsUpdate)
            {
                _repository.Update(Discipline);
                Message = "Данные успешно обновлены";
            }
            else 
            {
                _repository.Insert(Discipline);
                Message = "Данные успешно добавлены";
            }
                
        } catch (Exception ex)
        {
            Message = ex.Message;
        }

        return Page();
    }
}
