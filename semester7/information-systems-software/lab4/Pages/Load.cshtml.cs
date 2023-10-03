using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace lab3.Pages;

[BindProperties]
public class LoadModel : PageModel
{
    public IFormFile Upload { get; set; }

    public string? Message { get; set; }

    private IDisciplineRepository _repository;

    public LoadModel(IDisciplineRepository repository)
    {
        _repository = repository;
    }

    public void OnPost()
    {
        using var stream = Upload.OpenReadStream();
        try {
            _repository.LoadXML(stream);
            Message = "Данные успешно загружены";
        } catch (Exception ex)
        {
            Message = ex.Message;
        }        
    }
}
