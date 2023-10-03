using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace lab3.Pages;

[BindProperties]
public class IndexModel : PageModel
{
    public IEnumerable<Discipline> Disciplines { 
        get => _repository.GetAll(); }

    private IDisciplineRepository _repository;

    public IndexModel(IDisciplineRepository repository)
    {
        _repository = repository;
    }

    public FileResult OnPostSaveXML()
    {
        var stream = new MemoryStream();
        _repository.WriteXML(stream);
        stream.Position = 0;
        var contentType = "application/xml";
        return File(stream, contentType, "data.xml");
    }

    public void OnPostClear()
    {
        _repository.Clear();
    }
}
